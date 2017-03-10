cmake_minimum_required (VERSION 2.6)

project (blessings)

set (blessings_VERSION_MAJOR 0)
set (blessings_VERSION_MINOR 1)

set (CMAKE_BINARY_DIR "build")

add_subdirectory ("symbol_utf8")

set (blessings_SOURCE
	linux/write_stream_linux.cpp
	linux/write_stream_linux_symbol_utf8.cpp
	linux/ANSI/ansi_symbol_table_symbol_utf8.cpp
	linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.cpp
	monitor_symbol_utf8_property_ansi.cpp
	property.cpp
)

add_library (blessings_static STATIC ${blessings_SOURCE})
add_library (blessings_shared SHARED ${blessings_SOURCE})
set_target_properties(blessings_static PROPERTIES
	COMPILE_FLAGS "-O3 -std=c++14"
	OUTPUT_NAME "blessings"
)
set_target_properties(blessings_shared PROPERTIES
	COMPILE_FLAGS "-O3 -std=c++14"
	OUTPUT_NAME "blessings"
)

add_library (blessings_static_test STATIC EXCLUDE_FROM_ALL ${blessings_SOURCE})
add_library (blessings_shared_test STATIC EXCLUDE_FROM_ALL ${blessings_SOURCE})
set_target_properties(blessings_static_test PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -std=c++14"
	OUTPUT_NAME "blessings_test"
)
set_target_properties(blessings_shared_test PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -std=c++14"
	OUTPUT_NAME "blessings_test"
)

add_executable (work EXCLUDE_FROM_ALL test.cpp)
set_target_properties(work PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -std=c++14"
)

target_link_libraries (work blessings_utf8_static_test blessings_static_test stdc++)
