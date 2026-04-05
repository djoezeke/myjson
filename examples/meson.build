# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================


if myjson_build_examples

    #===========================
    # C++ Library API Examples #
    #===========================

	myjson_examples = []

    foreach example : myjson_examples

		exe = executable(
                        example,
                        'apis/' + example,
                        include_directories: myjson_include_dirs,
                        dependencies: [myjson_dep],
            install: false
        )
        
	endforeach

    #===========================
    # C Library API Examples   #
    #===========================

	myjsonc_examples = []

    foreach example : myjsonc_examples

		exe = executable(
                        example + 'c',
            'apis/' + example,
                        include_directories: myjson_include_dirs,
                        dependencies: [myjsonc_dep],
            install: false
        )

	endforeach

endif

# ===================================================================
