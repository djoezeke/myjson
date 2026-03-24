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
            example, example,
            include_directories: incdir,
            link_with: [myjson_lib],
            install: false
        )
        
	endforeach

    #===========================
    # C Library API Examples   #
    #===========================

	myjsonc_examples = []

    foreach example : myjsonc_examples

		exe = executable(example + 'c',
            'apis/' + example,
            include_directories: incdir,
            link_with: [myjsonc_lib], 
            install: false
        )

	endforeach

endif

# ===================================================================
