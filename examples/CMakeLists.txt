# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Example Function
#--------------------------------------------------------------------

# add a new target which is an example
# example: myjson_add_example(example
#                     SOURCES example.cpp
#                     DEPENDS Myjson::Myjson)
function(myjson_add_example target)

    # parse the arguments
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling myjson_add_example: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})

    # create the target
    add_executable(${target} ${THIS_SOURCES})

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "Examples")

    # set the Visual Studio startup path for debugging
    set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    target_include_directories(${target} PRIVATE ${MYJSON_INCLUDE_DIR}>)

    # link the target to its dependencies
    target_link_libraries(${target} PRIVATE ${THIS_DEPENDS})

    # Enable support for UTF-8 characters in source code
    if(MSVC)
        target_compile_options(${target} PRIVATE /utf-8)
    endif()
endfunction()

#--------------------------------------------------------------------
# Build Api Example Projects
#--------------------------------------------------------------------
add_subdirectory(apis)

#--------------------------------------------------------------------
# Build Usage Tutorial Projects
#--------------------------------------------------------------------
add_subdirectory(tutorials)

# ===================================================================
