cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

set (MYJSON_VERSION_MAJOR 0)
set (MYJSON_VERSION_MINOR 1)
set (MYJSON_VERSION_PATCH 1)
set (MYJSON_VERSION_STRING ${MYJSON_VERSION_MAJOR}.${MYJSON_VERSION_MINOR}.${MYJSON_VERSION_PATCH})

project(Myyaml
        VERSION ${MYJSON_VERSION_STRING} 
        DESCRIPTION "Json parser for C/C++"
        HOMEPAGE_URL "https://github.com/djoezeke/myjson"
        LANGUAGES  C
)

#--------------------------------------------------------------------
# Preparations depending on the specified build options  
#--------------------------------------------------------------------

# Check if this project is the main project
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MYJSON_IS_TOP_LEVEL ON)
else()
  set(MYJSON_IS_TOP_LEVEL OFF)
endif()

#--------------------------------------------------------------------
# Configure variables for the library   
#--------------------------------------------------------------------
include(GNUInstallDirs)

set(MYJSON_LIB_NAME "myjson" CACHE STRING "Base name of library output name")

set(MYJSON_SOURCES myjson.c)
set(MYJSON_INCLUDES myjson.h)
set(MYJSON_TARGET_NAME  ${MYJSON_LIB_NAME})

# Set required C/C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

option(MYJSON_BUILD_SHARED "Build shared library" OFF)
option(MYJSON_BUILD_EXAMPLES "Build the ${PROJECT_NAME} example applications" ${MYJSON_IS_TOP_LEVEL})
option(MYJSON_BUILD_TESTS "Build the ${PROJECT_NAME} test programs" ${MYJSON_IS_TOP_LEVEL})
option(MYJSON_INSTALL "Generate installation target" ${MYJSON_IS_TOP_LEVEL})

set(MYJSON_CMAKE_CONFIG_NAME "${PROJECT_NAME}Config")
set(MYJSON_CMAKE_TARGET_NAME "${PROJECT_NAME}Target")

set(MYJSON_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MYJSON_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(MYJSON_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "Install directory path for config files.")

set(MYJSON_CMAKE_CONFIG_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(MYJSON_CMAKE_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/${MYJSON_CMAKE_CONFIG_NAME}.cmake.in")
set(MYJSON_CMAKE_VERSION_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/${MYJSON_CMAKE_CONFIG_NAME}Version.cmake.in")
set(MYJSON_CMAKE_PACKAGE_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/pkg-config.pc.in")

set(MYJSON_CMAKE_CONFIG_DIR  ${CMAKE_CURRENT_BINARY_DIR})
set(MYJSON_CMAKE_CONFIG_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake)
set(MYJSON_CMAKE_TARGETS_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake)
set(MYJSON_CMAKE_PACKAGE_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}.pc)
set(MYJSON_CMAKE_VERSION_CONFIG_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake)

#--------------------------------------------------------------------
# Build library targets
#--------------------------------------------------------------------

if(MYJSON_BUILD_SHARED)
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif()

add_library(${MYJSON_LIB_NAME} ${MYJSON_SOURCES})

target_include_directories(${MYJSON_LIB_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${MYJSON_INCLUDE_BUILD_DIR}>
        $<INSTALL_INTERFACE:${MYJSON_INCLUDE_INSTALL_DIR}>
)

#--------------------------------------------------------------------
# Configurations
#--------------------------------------------------------------------

# Default to build type "Release" unless tests are being built
if(NOT CMAKE_BUILD_TYPE)
	if (NOT MYJSON_BUILD_TESTS)
		message(STATUS "No build type selected, default to Release")
		set(CMAKE_BUILD_TYPE "Release")
	else()
		message(STATUS "No build type selected but tests are being built, default to Debug")
		set(CMAKE_BUILD_TYPE "Debug")
	endif()
endif()

if(BUILD_SHARED_LIBS)
    set_target_properties(${MYJSON_LIB_NAME} 
    PROPERTIES DEFINE_SYMBOL MYJSON_BUILD_SHARED
    )
else()
    set_target_properties(${MYJSON_LIB_NAME} 
    PROPERTIES DEFINE_SYMBOL MYJSON_BUILD_STATIC
    )
endif()

# Output directories for a build tree
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

#--------------------------------------------------------------------
# Add Project subdirectories
#--------------------------------------------------------------------

# Build the example apps   
if(MYJSON_BUILD_EXAMPLES)
    add_subdirectory(samples)
endif()

# Build the test apps   
if(MYJSON_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)

    # Set the unit test app project as the Visual Studio startup project
    # if the target compiler is some version of Microsoft Visual C++ and
    # if this project is the main project.
    if(MSVC AND CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyYamlUnitTest)
    endif()
endif()

#--------------------------------------------------------------------
# Install a pkg-config file
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Configure package.
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

configure_file(
    ${MYJSON_CMAKE_CONFIG_TEMPLATE}
    ${MYJSON_CMAKE_CONFIG_FILE}
    @ONLY
)

configure_file(
    ${MYJSON_CMAKE_VERSION_CONFIG_TEMPLATE}
    ${MYJSON_CMAKE_VERSION_CONFIG_FILE}
    @ONLY
)

configure_file(
    "${MYJSON_CMAKE_PACKAGE_CONFIG_TEMPLATE}"
    "${MYJSON_CMAKE_PACKAGE_FILE}"
)

#--------------------------------------------------------------------
# Install package.
#--------------------------------------------------------------------
if(MYJSON_INSTALL)
    install(
        DIRECTORY ${MYJSON_INCLUDE_BUILD_DIR}
        DESTINATION ${MYJSON_INCLUDE_INSTALL_DIR}
    )

    install(
        FILES ${MYJSON_CMAKE_CONFIG_FILE} ${MYJSON_CMAKE_VERSION_CONFIG_FILE}
        DESTINATION ${MYJSON_CONFIG_INSTALL_DIR}
    )

    export(
        TARGETS ${MYJSON_TARGET_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE ${MYJSON_CMAKE_TARGETS_FILE}
    )

    install(
        TARGETS ${MYJSON_TARGET_NAME}
        EXPORT ${MYJSON_CMAKE_TARGET_NAME}
    )

    install(
        EXPORT ${MYJSON_CMAKE_TARGET_NAME}
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${MYJSON_CONFIG_INSTALL_DIR}
    )

    install(
        FILES "${MYJSON_CMAKE_PACKAGE_FILE}"
        DESTINATION ${MYJSON_CONFIG_INSTALL_DIR}
    )

endif()
