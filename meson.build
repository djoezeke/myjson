# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

project('myjson',
	['c', 'cpp'],
	version : '0.1.0',
	license : 'MIT',
	default_options : [
		'buildtype=release',
		'default_library=static',
		],
  	subproject_dir: 'tests/vendor'
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
myjson_install = get_option('myjson_install') and not myjson_is_subproject
myjson_build_c_api = get_option('myjson_build_c_api')

src_files = []

#--------------------------------------------------------------------
# Build Project Libraries.
#--------------------------------------------------------------------

#===========================
# Build C++ Library        #
#===========================

myjson_lib = library(
	'myjson',
	'src/myjson.cpp',
	include_directories : myjson_include_dirs,
	install : myjson_install,
)

#===========================
# Build C Library          #
#===========================

myjson_dep = declare_dependency(
	link_with : myjson_lib,
	include_directories : myjson_include_dirs,
)

myjsonc_dep = myjson_dep

if myjson_build_c_api
	myjsonc_lib = library(
		'myjsonc', 
		'src/myjsonc.cpp',
		include_directories : myjson_include_dirs,
		link_with : myjson_lib,
		install : myjson_install,
	)

	myjsonc_dep = declare_dependency(
		link_with : myjsonc_lib,
		include_directories : myjson_include_dirs,
	)
endif

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

	if myjson_install
		install_headers('include/myjson/myjson.h', subdir : 'myjson')
		install_headers('include/myjson/myjson.hpp', subdir : 'myjson')
	endif

	pkgc = import('pkgconfig')
	pkg_libraries = [myjson_lib]
	if myjson_build_c_api
		pkg_libraries += [myjsonc_lib]
	endif
	pkgc.generate(
		name : meson.project_name(),
		version: meson.project_version(),
		description: 'TOML for Modern C/C++',
		url: 'https://github.com/djoezeke/myjson',
		libraries: pkg_libraries,
		subdirs : 'myjson',
	)

endif

# ===================================================================
