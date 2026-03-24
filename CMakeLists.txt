# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)

# define a macro that helps defining an option
macro(myjson_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

set (MYJSON_VERSION_MAJOR 0)
set (MYJSON_VERSION_MINOR 1)
set (MYJSON_VERSION_PATCH 1)

set (MYJSON_VERSION_STRING "0.1.0")

project(Myjson
        VERSION ${MYJSON_VERSION_STRING} 
        DESCRIPTION "Json parser for C/C++"
        HOMEPAGE_URL "https://github.com/djoezeke/myjson"
        LANGUAGES  C CXX
)

#-------------------------------------------------------------------------------------------------------
# Cmake functions
#-------------------------------------------------------------------------------------------------------
include(CMakeDependentOption)

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
# Set default build to release
#--------------------------------------------------------------------

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif ()

#--------------------------------------------------------------------
# Compiler config
#--------------------------------------------------------------------

if (NOT CMAKE_CXX_STANDARD)
    # If CMAKE_CXX_STANDARD is not set, configure it to 17 by default
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
elseif (CMAKE_CXX_STANDARD LESS 11)
    # If CMAKE_CXX_STANDARD is set but less than 11, issue a fatal error
    message(FATAL_ERROR "Myjson requires at least C++11. Please set CMAKE_CXX_STANDARD to 11 or higher.")
endif ()

# Add UTF-8 encoding support for MSVC compiler.
# This ensures that the MSVC compiler interprets source files as UTF-8 encoded,
# which is useful for projects containing non-ASCII characters in source files.
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#--------------------------------------------------------------------
# Configure variables for the library   
#--------------------------------------------------------------------

set(MYJSON_SOURECS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

myjson_set_option(MYJSON_ENABLE_WARNING ${MYJSON_IS_TOP_LEVEL} BOOL "ON to enable warning messages.")

myjson_set_option(MYJSON_BUILD_CMYJSON ON BOOL "ON to build MYJSONC")

# add an option for choosing the build type (shared or static)
myjson_set_option(MYJSON_BUILD_SHARED ON BOOL "ON to build MYJSON as shared libraries, OFF to build it as static libraries")

myjson_set_option(MYJSON_INSTALL ${MYJSON_IS_TOP_LEVEL} BOOL "ON to Generate installation target" )
cmake_dependent_option(MYJSON_INSTALL_DOCS "Install docs for Myjson" ${MYJSON_IS_TOP_LEVEL} "MYJSON_INSTALL" ON)
cmake_dependent_option(MYJSON_INSTALL_TESTS "Install test-cases" ${MYJSON_IS_TOP_LEVEL} "MYJSON_INSTALL" ON)
cmake_dependent_option(MYJSON_INSTALL_CPACK "Create binary Myjson archive using CPack" ${MYJSON_IS_TOP_LEVEL} "MYJSON_INSTALL" ON)

# option(MYJSON_BUILD_SHARED "Build shared library" ${MYJSON_IS_TOP_LEVEL})
# option(MYJSON_BUILD_DEBUG "Build debug version of library" ${MYJSON_IS_TOP_LEVEL})
# option(MYJSON_ENABLE_DOXYGEN "Build documentation with Doxygen." ${MYJSON_IS_TOP_LEVEL})

if(DEFINED BUILD_SHARED_LIBS)
    # When defined, use BUILD_SHARED_LIBS as default
    if(BUILD_SHARED_LIBS)
        set(MYJSON_STATIC OFF)
    else()
        set(MYJSON_STATIC ON)
    endif()
else()
    # Default to just building the static library
    set(MYJSON_STATIC ON)
endif()

# Add compiler warnings
if(MYJSON_ENABLE_WARNINGS)
    if(MSVC)
        set(MYJSON_WARNINGS /WX /W4 /permissive-)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        set(MYJSON_WARNINGS -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
    endif()
endif()

option(MYJSON_ENABLE_SANITIZERS "Enable sanitizers" OFF)
if(MYJSON_ENABLE_SANITIZERS)
    string(APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=undefined")
endif()

option(MYJSON_ENABLE_STDLIB_ASSERTIONS "Enable standard library assertions" OFF)
if(MYJSON_ENABLE_STDLIB_ASSERTIONS)
    # intentionally using `add_compile_definitions` here to propagate defines to subdirectories
    add_compile_definitions(_GLIBCXX_ASSERTIONS=1)                                   # see https://gcc.gnu.org/wiki/LibstdcxxDebugMode

    # Xcode has a property to control this - adding the define ourselves causes multiple definitions
    if(XCODE)
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_STANDARD_LIBRARY_HARDENING "Yes (extensive)")
    else()
        add_compile_definitions(_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE) # see https://libcxx.llvm.org/Hardening.html
    endif()
endif()

#--------------------------------------------------------------------
# Macro to Build libraries
#--------------------------------------------------------------------

include(CMakeParseArguments)

# example: myjson_make_library(Myjson
#                       SOURCES myjsonc.cpp ...
#                       DEPENDS Myjson::MyjsonC
#                       [STATIC]) # Always create a static library
macro(myjson_make_library library)

    # parse the arguments
    cmake_parse_arguments(THIS "" "DEPENDS" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling myjson_make_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create the target
    string(TOLOWER ${library} target)
    if(MYJSON_STATIC)
        add_library(${target} STATIC ${THIS_SOURCES})
    else()
        add_library(${target} SHARED ${THIS_SOURCES})
    endif()
    add_library(Myjson::${library} ALIAS ${target})

    # require C11 support
    target_compile_features(${target} PUBLIC c_std_11)

    # enable C++17 support
    target_compile_features(${target} PUBLIC cxx_std_17)

    # define the export symbol of the library
    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    # define the export name of the library
    set_target_properties(${target} PROPERTIES EXPORT_NAME Myjson::${library})

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "Myjson")

    # add <project>/include as public include directory
    target_include_directories(${target} 
        PUBLIC $<BUILD_INTERFACE:${MYJSON_INCLUDE_BUILD_DIR}>
        INTERFACE $<INSTALL_INTERFACE:${MYJSON_INCLUDE_INSTALL_DIR}>
    )

    if(NOT MYJSON_STATIC)
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
            # include the major version number in Windows shared library names (but not import library names)
            set_target_properties(${target} PROPERTIES SUFFIX "-${PROJECT_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")

            # on Windows/gcc get rid of "lib" prefix for shared libraries,
            # and transform the ".dll.a" suffix into ".a" for import libraries
            if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                set_target_properties(${target} PROPERTIES PREFIX "")
                set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
            endif()
        endif()
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX "")
        set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX "")
        set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX "")
    endif()

    # set the version and soversion of the target (for compatible systems -- mostly Linuxes)
    set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

    # foreach(WARNING ${MYJSON_WARNINGS})
    #     set_target_properties(${target} PROPERTIES APPEND_STRING COMPILE_FLAGS " ${WARNING}")
    # endforeach()

    if(NOT MYJSON_STATIC)
        # define MYJSON_BUILD_SHARED if the build type is set to 'shared'
        target_compile_definitions(${target} PRIVATE MYJSON_BUILD_SHARED)
        set_target_properties(${target} PROPERTIES DEFINE_SYMBOL MYJSON_BUILD_SHARED)
    else()
        # define MYJSON_BUILD_STATIC if the build type is set to 'static'
        target_compile_definitions(${target} PRIVATE MYJSON_BUILD_STATIC)
        set_target_properties(${target} PROPERTIES DEFINE_SYMBOL MYJSON_BUILD_STATIC)
    endif()

    # Enable support for UTF-8 characters in source code
    if(MSVC)
        target_compile_options(${target} PRIVATE /utf-8)
    endif()
endmacro()

#--------------------------------------------------------------------
# Build library targets
#--------------------------------------------------------------------

# If both shared and static libs are build at once with MSVC it generates a
# shared library consisting of
#
# * a DLL (that contains the actual code) with filename suffix `.dll`,
# * a correspoding import library (against which users should link) with
#   filename suffix `.lib`.
#
# and a static library with filename suffix `.lib`
#
# As both, the shared import library and the static library share the same
# basename and suffix one would overwrite the other.
#
# To solve this issue we set the PREFIX for *static* libs explicitely so MSVC
# will build:
#
# * shared: myjson.dll
# * import: myjson.lib
# * static: libmyjson.lib
#
# and this for debug:
#
# * shared: myjson-d.dll
# * import: myjson-d.lib
# * static: libmyjson-d.lib
#
# As all other platforms already set `PREFIX` for all lib types they remain
# unchanged. Therefore no `if(MSVC)` check is needed here.

# define the myjson target
myjson_make_library(Myjson
                    SOURCES src/myjson.cpp
                    )

# define the myjsonc target
myjson_make_library(MyjsonC
                    SOURCES src/myjsonc.cpp
                    DEPENDS Myjson::Myjson
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

# Output directories for a build tree
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#--------------------------------------------------------------------
# Add Project subdirectories
#--------------------------------------------------------------------

# add an option for building the API documentation
myjson_set_option(MYJSON_BUILD_DOCS OFF BOOL "ON to generate the API documentation")

# Build the documentation   
if(MYJSON_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# add an option for building the examples
# Build examples and tests by default for top-level project
myjson_set_option(MYJSON_BUILD_EXAMPLES ${MYJSON_IS_TOP_LEVEL} BOOL "ON to build the examples")

# Build the example apps   
if(MYJSON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# add an option for building the tests
# Build tests by default for top-level project
myjson_set_option(MYJSON_BUILD_TESTS ${MYJSON_IS_TOP_LEVEL} BOOL "ON to build the test suite")

# Build the test apps   
if(MYJSON_BUILD_TESTS)
    include(CTest)
    enable_testing()

    if (MYJSON_USE_VALGRIND)
        # find valgrind
        find_program(VALGRIND_EXE NAMES valgrind)
        if (NOT VALGRIND_EXE)
            message(WARNING "Valgrind not found")
        endif ()

        # set valgrind params
        set(VALGRIND_OPTIONS "--tool=memcheck --leak-check=full --leak-resolution=med --show-leak-kinds=all --track-origins=yes --vgdb=no --fair-sched=yes")

        # add memcheck test action to ctest
        include(CTest)
    endif ()

    add_subdirectory(tests)

    # Set the unit test app project as the Visual Studio startup project
    # if the target compiler is some version of Microsoft Visual C++ and
    # if this project is the main project.
    if(MSVC AND CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyjsonUnitTest)
    endif()
endif()

#--------------------------------------------------------------------
# Install.
#--------------------------------------------------------------------

if(MYJSON_INSTALL)

    set(MYJSON_CMAKE_CONFIG_NAME "${PROJECT_NAME}Config")
    set(MYJSON_CMAKE_TARGET_NAME "${PROJECT_NAME}Target")

    set(MYJSON_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(MYJSON_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
    set(MYJSON_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "Install directory path for config files.")

    set(MYJSON_CMAKE_CONFIG_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    set(MYJSON_CMAKE_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/${MYJSON_CMAKE_CONFIG_NAME}.cmake.in")
    set(MYJSON_CMAKE_VERSION_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/${MYJSON_CMAKE_CONFIG_NAME}Version.cmake.in")
    set(MYJSON_CMAKE_PACKAGE_CONFIG_TEMPLATE "${MYJSON_CMAKE_CONFIG_TEMPLATE_DIR}/${PROJECT_NAME}.pc.in")

    set(MYJSON_CMAKE_CONFIG_DIR  ${CMAKE_CURRENT_BINARY_DIR})
    set(MYJSON_CMAKE_CONFIG_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake)
    set(MYJSON_CMAKE_TARGETS_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake)
    set(MYJSON_CMAKE_PACKAGE_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}.pc)
    set(MYJSON_CMAKE_VERSION_CONFIG_FILE  ${MYJSON_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake)

    #--------------------------------------------------------------------
    # Configure package.
    #--------------------------------------------------------------------

    # we use the paths from the cmake GNUInstallDirs library as defaults
    # you can override these if you like
    # https://cmake.org/cmake/help/latest/library/GNUInstallDirs.html
    include(GNUInstallDirs)
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

    # # install headers
    # install(DIRECTORY ${MYJSON_INCLUDE_BUILD_DIR}/myjson DESTINATION ${MYJSON_INCLUDE_INSTALL_DIR})

    # # install targets
    # install(TARGETS myjson myjsonc
    #     EXPORT ${MYJSON_CMAKE_TARGET_NAME}
    #     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    #     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    #     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    #     INCLUDES DESTINATION ${MYJSON_INCLUDE_INSTALL_DIR}
    # )

    # # export targets for find_package consumers
    # install(EXPORT ${MYJSON_CMAKE_TARGET_NAME}
    #     FILE ${MYJSON_CMAKE_TARGETS_FILE}
    #     NAMESPACE ${PROJECT_NAME}::
    #     DESTINATION ${MYJSON_CONFIG_INSTALL_DIR}
    # )

    # # install package config files
    # install(FILES ${MYJSON_CMAKE_CONFIG_FILE} ${MYJSON_CMAKE_VERSION_CONFIG_FILE} ${MYJSON_CMAKE_PACKAGE_FILE}
    #     DESTINATION ${MYJSON_CONFIG_INSTALL_DIR}
    # )

    install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
    install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    
    #--------------------------------------------------------------------
    # Package with CPack.
    #--------------------------------------------------------------------

    if(MYJSON_INSTALL_CPACK)
        set(CPACK_PACKAGE_NAME "Myjson")
        set(CPACK_PACKAGE_NAME_SUMMARY "Simple and Fast Json Parser")
        set(CPACK_PACKAGE_CONTACT "djoezeke")
        set(CPACK_PACKAGE_VENDOR "Myjson Contributers")
        set(CPACK_PACKAGE_FILE_NAME "myjson-${PROJECT_VERSION}")
        set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
        set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
        set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
        set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
        set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
        set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
        set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
        set(CPACK_PACKAGE_INSTALL_DIRECTORY "Myjson ${PROJECT_VERSION}")
        # set(CPACK_MONOLITHIC_INSTALL ON)
        set(CPACK_GENERATOR "ZIP;TGZ;DEB;RPM") # Remove this, if you want the NSIS installer on Windows
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS OFF) # can be used to generate deps, slow and requires tools.
        set(CPACK_DEBIAN_PACKAGE_NAME "lib${CPACK_PACKAGE_NAME}-dev")
        set(CPACK_RPM_PACKAGE_NAME "lib${CPACK_PACKAGE_NAME}-devel")

        include(CPack)

    endif()

endif()

#--------------------------------------------------------------------
# Clang CI
#--------------------------------------------------------------------

# add an option for clang-format
myjson_set_option(MYJSON_ENABLE_CLANG_FORMAT ${MYJSON_IS_TOP_LEVEL} BOOL "ON to Add clang-format target")

myjson_set_option(CLANG_FORMAT_EXECUTABLE "clang-format" STRING "Override clang-format executable, requires version 17")
if(MYJSON_ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXE NAMES CLANG_FORMAT_EXECUTABLE)
    if(CLANG_FORMAT_EXE)
        add_custom_target(clang-format
            COMMAND ${CLANG_FORMAT_EXE} -i --style=file ${MYJSON_SOURECS_DIR}/* ${MYJSON_INCLUDE_BUILD_DIR}/*
            COMMENT "Format project sources with clang-format"
        )
    else()
        message(WARNING "clang-format requested but not found on PATH")
    endif()
endif()

# add an option for clang-tidy
myjson_set_option(MYJSON_ENABLE_CLANG_TIDY ${MYJSON_IS_TOP_LEVEL} BOOL "ON to Add clang-tidy target")

myjson_set_option(CLANG_TIDY_EXECUTABLE "clang-tidy" STRING "Override clang-tidy executable, requires minimum version 14")
if(MYJSON_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES CLANG_TIDY_EXECUTABLE)
    if(CLANG_TIDY_EXE)
        add_custom_target(clang-tidy
            COMMAND ${CLANG_TIDY_EXE} --config-file=.clang-tidy ${MYJSON_SOURECS_DIR}/* ${MYJSON_INCLUDE_BUILD_DIR}/*
            COMMENT "Tidy project sources with clang-tidy"
        )
    else()
        message(WARNING "clang-tidy requested but not found on PATH")
    endif()
endif()

#--------------------------------------------------------------------
# Uninstall Target
#--------------------------------------------------------------------

if(MYJSON_UNINSTALL)
    if(NOT TARGET uninstall)
        configure_file(cmake/cmake_uninstall.cmake.in cmake_uninstall.cmake IMMEDIATE @ONLY)

        add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
    endif()
endif()
