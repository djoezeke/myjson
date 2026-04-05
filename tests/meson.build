# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

if myjson_build_tests
	catch2_include_dirs = include_directories('vendor/Catch2/src')

	catch2_dep = dependency(
		'catch2-with-main',
        fallback: ['Catch2', 'catch2_with_main_dep'],
		required: true
	)

    #===========================
    # C++ Library Tests        #
    #===========================

	myjson_test_sources = [
		'cxx/Main.test.cpp',
	]

	myjson_test_exe = executable(
		'myjson_cpp_tests', 
		myjson_test_sources,
		include_directories: [myjson_include_dirs, catch2_include_dirs],
		dependencies: [myjson_dep, catch2_dep], 
		install: false
	)

	test('myjson_cpp_tests', myjson_test_exe)

    #===========================
    # C Library Tests          #
    #===========================

	myjsonc_test_sources = [
		'c/Main.test.cpp'
	]

	myjsonc_test_exe = executable(
		'myjson_c_tests', 
		myjsonc_test_sources,
		include_directories: [myjson_include_dirs, catch2_include_dirs],
		dependencies: [myjsonc_dep, catch2_dep], 
		install: false
	)

	test('myjson_c_tests', myjsonc_test_exe)

endif

# ===================================================================
