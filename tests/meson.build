# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

if myjson_build_tests

    #===========================
    # C++ Library Tests        #
    #===========================

	myjson_test_sources = [
		'cxx/Version.test.cpp'
	]

	myjson_test_exe = executable(
		myjson_test, 
		myjson_test_sources,
		include_directories: myjson_include_dirs,
		link_with: [myjson_lib], 
		install: false
	)

	test(myjson_test, myjson_test_exe)

    #===========================
    # C Library Tests          #
    #===========================

	myjsonc_test_sources = [
		'c/Version.test.cpp'
	]

	myjsonc_test_exe = executable(
		myjsonc_test, 
		myjsonc_test_sources,
		include_directories: myjson_include_dirs,
		link_with: [myjsonc_lib], 
		install: false
	)

	test(myjsonc_test, myjsonc_test_exe)

endif

# ===================================================================
