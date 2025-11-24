cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)

#--------------------------------------------------------------------
# Basic Test Configures   
#--------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(WIN32)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("." "../")

set(MYJSON_TEST_LIB_NAME ${MYJSON_LIB_NAME}-d)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
add_library(${MYJSON_TEST_LIB_NAME} ../${MYJSON_SOURCES})

target_include_directories(${MYJSON_TEST_LIB_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${MYJSON_INCLUDE_BUILD_DIR}>
)

set_target_properties(${MYJSON_TEST_LIB_NAME} 
    PROPERTIES DEFINE_SYMBOL MYJSON_BUILD_SHARED
)

# include(CTest)

# include(FetchContent)

# FetchContent_Declare(
#     Catch2
#     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#     GIT_TAG        v3.11.0 # or a later release
#     )

# FetchContent_MakeAvailable(Catch2)

include(CTest)

set (C_TEST_SOURCES CMAKE_CURRENT_SOURCE_DIR/c/)
set (CXX_TEST_SOURCES CMAKE_CURRENT_SOURCE_DIR/cxx/)

# define the sources of the self test
# Please keep these ordered alphabetically
set(TEST_CXX_SOURCES
  ${CXX_TEST_SOURCES}/test.cpp
)

add_executable(CxxTest ${TEST_CXX_SOURCES} ${TEST_HEADERS})
target_include_directories(CxxTest PRIVATE ${CXX_TEST_DIR})
target_link_libraries(CxxTest PRIVATE Catch2WithMain)

if(BUILD_SHARED_LIBS AND WIN32)
  add_custom_command(TARGET CxxTest PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Catch2>
    $<TARGET_FILE:Catch2WithMain> $<TARGET_FILE_DIR:CxxTest>
  )
endif()

