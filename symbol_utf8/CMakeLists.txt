project (blessings_utf8)

set (blessings_utf8_VERSION_MAJOR 0)
set (blessings_utf8_VERSION_MINOR 1)

set (CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set (blessings_utf8_SOURCE
	symbol_utf8.cpp
	string_utf8.cpp
)

add_library (blessings_utf8_static STATIC ${blessings_utf8_SOURCE})
add_library (blessings_utf8_shared SHARED ${blessings_utf8_SOURCE})
set_target_properties(blessings_utf8_static PROPERTIES
	COMPILE_FLAGS "-O3 -std=c++14"
	OUTPUT_NAME "blessings_utf8"
)
set_target_properties(blessings_utf8_shared PROPERTIES
	COMPILE_FLAGS "-O3 -std=c++14"
	OUTPUT_NAME "blessings_utf8"
)

add_library (blessings_utf8_static_test STATIC EXCLUDE_FROM_ALL ${blessings_utf8_SOURCE})
add_library (blessings_utf8_shared_test SHARED EXCLUDE_FROM_ALL ${blessings_utf8_SOURCE})
set_target_properties(blessings_utf8_static_test PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -std=c++14"
	OUTPUT_NAME "blessings_utf8_test"
)
set_target_properties(blessings_utf8_shared_test PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -std=c++14"
	OUTPUT_NAME "blessings_utf8_test"
)
