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

#--------------------------------------------------------------------
# Test Functions
#--------------------------------------------------------------------

function(add_c_test NAME)
  add_executable(${NAME} ${NAME}.c)
  target_link_libraries(${NAME} PRIVATE ${MYJSON_LIB_NAME})
  set_property(TARGET ${NAME} PROPERTY C_STANDARD 17)
  set_target_properties(${NAME} PROPERTIES DEFINE_SYMBOL MYJSON_IMPORT)
  add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

function(add_cpp_test NAME)
  add_executable(${NAME} ${NAME}.cpp)
  target_link_libraries(${NAME} PRIVATE ${MYJSON_LIB_NAME})
  set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 17)
  set_target_properties(${NAME} PROPERTIES DEFINE_SYMBOL MYJSON_IMPORT)
  add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

#--------------------------------------------------------------------
# Recursively add Tests
#--------------------------------------------------------------------

# Automatically add all .c tests in this folder
file(GLOB C_TEST_SOURCES "*.c")
foreach(TEST_FILE ${C_TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_c_test(${TEST_NAME})
endforeach()

# Automatically add all .cpp tests in this folder
file(GLOB CPP_TEST_SOURCES "*.cpp")
foreach(TEST_FILE ${CPP_TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_cpp_test(${TEST_NAME})
endforeach()
