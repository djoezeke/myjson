# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

project('myjson',
	'cpp',
	version : '0.1.0',
	license : 'MIT',
	default_options : [
		'buildtype=release',
		'default_library=static',
		'cpp_std=c++17'
		]
)

compiler = meson.get_compiler('cpp')
message('target cpu_family: @0@'.format(host_machine.cpu_family()))
message('target cpu: @0@'.format(host_machine.cpu()))
message('target system: @0@'.format(host_machine.system()))
message('target endian: @0@'.format(host_machine.endian()))

#--------------------------------------------------------------------
# Configure Project Variables.   
#--------------------------------------------------------------------

license = files('LICENSE')

myjson_is_subproject = meson.is_subproject()
myjson_include_dirs = include_directories('include')
myjson_build_tests = get_option('myjson_build_tests') and not myjson_is_subproject
myjson_build_examples = get_option('myjson_build_examples') and not myjson_is_subproject

src_files = []

#--------------------------------------------------------------------
# Build Project Libraries.
#--------------------------------------------------------------------

#===========================
# Build C++ Library        #
#===========================

myjson_lib = static_library(
	'myjson',
	'src/myjson.cpp',
	include_directories : myjson_include_dirs,
	install : true,
)

#===========================
# Build C Library          #
#===========================

myjsonc_lib = static_library(
	'myjsonc', 
	'src/myjsonc.cpp',
	include_directories : myjson_include_dirs,
	link_with : myjson_lib,
	install : true,
)

#--------------------------------------------------------------------
# Add Project subdirectories.
#--------------------------------------------------------------------

if myjson_build_tests
	subdir('tests')
endif

if myjson_build_examples
	subdir('examples')
endif

#--------------------------------------------------------------------
# Install Project Packages.
#--------------------------------------------------------------------

if not meson.is_subproject()

	install_headers('include/myjson/myjson.h', subdir : 'myjson')
	install_headers('include/myjson/myjson.hpp', subdir : 'myjson')

	pkgc = import('pkgconfig')
	pkgc.generate(
		name : meson.project_name(),
		version: meson.project_version(),
		description: 'JSON for Modern C/C++',
		url: 'https://github.com/djoezeke/myjson',
	)

endif

# ===================================================================
