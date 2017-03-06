lib: lib_shared lib_static
build/symbol_utf8/string_utf8.o: \
 /home/shkiper/Код/Blessings/symbol_utf8/string_utf8.cpp \
 /home/shkiper/Код/Blessings/symbol_utf8/string_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/../error.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8_impl.hpp
	mkdir -p build/symbol_utf8/
	clang --std=c++11 -fpic -c -o build/symbol_utf8/string_utf8.o symbol_utf8/string_utf8.cpp
build/symbol_utf8/test_string_utf8.o: \
 /home/shkiper/Код/Blessings/symbol_utf8/test_string_utf8.cpp \
 /home/shkiper/Код/Blessings/symbol_utf8/test_string_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/string_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/../error.hpp
	mkdir -p build/symbol_utf8/
	clang --std=c++11 -fpic -c -o build/symbol_utf8/test_string_utf8.o symbol_utf8/test_string_utf8.cpp
build/symbol_utf8/symbol_utf8.o: \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/../error.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8_impl.hpp
	mkdir -p build/symbol_utf8/
	clang --std=c++11 -fpic -c -o build/symbol_utf8/symbol_utf8.o symbol_utf8/symbol_utf8.cpp
build/symbol_utf8/test_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/symbol_utf8/test_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/../error.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/test_symbol_utf8.hpp
	mkdir -p build/symbol_utf8/
	clang --std=c++11 -fpic -c -o build/symbol_utf8/test_symbol_utf8.o symbol_utf8/test_symbol_utf8.cpp
build/monitor_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/monitor_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/monitor_impl.hpp \
 /home/shkiper/Код/Blessings/monitor.hpp \
 /home/shkiper/Код/Blessings/additional_structs.hpp \
 /home/shkiper/Код/Blessings/terminal_io.hpp \
 /home/shkiper/Код/Blessings/property.hpp \
 /home/shkiper/Код/Blessings/error.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/monitor_symbol_utf8.o monitor_symbol_utf8.cpp
build/property.o: /home/shkiper/Код/Blessings/property.cpp \
 /home/shkiper/Код/Blessings/property.hpp \
 /home/shkiper/Код/Blessings/error.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/property.o property.cpp
build/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.o: \
 /home/shkiper/Код/Blessings/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.cpp \
 /home/shkiper/Код/Blessings/linux/ANSI/terminal_io_ansi_linux_impl.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/terminal_io_ansi_linux.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../additional_structs.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../error.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../terminal_io.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/ansi_symbol_table.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../property.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../symbol_utf8/symbol_utf8.hpp
	mkdir -p build/linux/ANSI/
	clang --std=c++11 -fpic -c -o build/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.o linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.cpp
build/linux/ANSI/ansi_symbol_table_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/linux/ANSI/ansi_symbol_table_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../symbol_utf8/../error.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/ansi_symbol_table.hpp
	mkdir -p build/linux/ANSI/
	clang --std=c++11 -fpic -c -o build/linux/ANSI/ansi_symbol_table_symbol_utf8.o linux/ANSI/ansi_symbol_table_symbol_utf8.cpp
build/linux/write_stream_linux.o: \
 /home/shkiper/Код/Blessings/linux/write_stream_linux.cpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/linux/../error.hpp
	mkdir -p build/linux/
	clang --std=c++11 -fpic -c -o build/linux/write_stream_linux.o linux/write_stream_linux.cpp
build/linux/write_stream_linux_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/linux/write_stream_linux_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux_impl.hpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/linux/../error.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol_utf8/symbol_utf8.hpp
	mkdir -p build/linux/
	clang --std=c++11 -fpic -c -o build/linux/write_stream_linux_symbol_utf8.o linux/write_stream_linux_symbol_utf8.cpp
build/test.o: /home/shkiper/Код/Blessings/test.cpp \
 /home/shkiper/Код/Blessings/symbol_utf8/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol_utf8/../error.hpp \
 /home/shkiper/Код/Blessings/property.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/terminal_io_ansi_linux.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../additional_structs.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../../terminal_io.hpp \
 /home/shkiper/Код/Blessings/linux/ANSI/../write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/monitor.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/test.o test.cpp
lib_static: build/symbol_utf8/string_utf8.o build/symbol_utf8/test_string_utf8.o build/symbol_utf8/symbol_utf8.o build/symbol_utf8/test_symbol_utf8.o build/monitor_symbol_utf8.o build/property.o build/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.o build/linux/ANSI/ansi_symbol_table_symbol_utf8.o build/linux/write_stream_linux.o build/linux/write_stream_linux_symbol_utf8.o
	ar rcs libblessings_static.a $^
lib_shared: build/symbol_utf8/string_utf8.o build/symbol_utf8/test_string_utf8.o build/symbol_utf8/symbol_utf8.o build/symbol_utf8/test_symbol_utf8.o build/monitor_symbol_utf8.o build/property.o build/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.o build/linux/ANSI/ansi_symbol_table_symbol_utf8.o build/linux/write_stream_linux.o build/linux/write_stream_linux_symbol_utf8.o
	clang --std=c++11 -shared -o libblessings_shared.so $^
test: build/symbol_utf8/string_utf8.o build/symbol_utf8/test_string_utf8.o build/symbol_utf8/symbol_utf8.o build/symbol_utf8/test_symbol_utf8.o build/monitor_symbol_utf8.o build/property.o build/linux/ANSI/terminal_io_ansi_linux_symbol_utf8_property_ansi.o build/linux/ANSI/ansi_symbol_table_symbol_utf8.o build/linux/write_stream_linux.o build/linux/write_stream_linux_symbol_utf8.o build/test.o
	clang --std=c++11 -o work -lstdc++ $^
clean:
	rm -rf build
	rm -f work
	rm -f libblessings_static.a
	rm -f libblessings_shared.so
install:
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp property.hpp $(HOME)/.prefix/usr/include/blessings/property.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp monitor_impl.hpp $(HOME)/.prefix/usr/include/blessings/monitor_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp terminal_io.hpp $(HOME)/.prefix/usr/include/blessings/terminal_io.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol_utf8/
	cp symbol_utf8/string_utf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol_utf8/string_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol_utf8/
	cp symbol_utf8/test_string_utf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol_utf8/test_string_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol_utf8/
	cp symbol_utf8/symbol_utf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol_utf8/symbol_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol_utf8/
	cp symbol_utf8/symbol_utf8_impl.hpp $(HOME)/.prefix/usr/include/blessings/symbol_utf8/symbol_utf8_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol_utf8/
	cp symbol_utf8/test_symbol_utf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol_utf8/test_symbol_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp monitor.hpp $(HOME)/.prefix/usr/include/blessings/monitor.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp additional_structs.hpp $(HOME)/.prefix/usr/include/blessings/additional_structs.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/ANSI/
	cp linux/ANSI/terminal_io_ansi_linux.hpp $(HOME)/.prefix/usr/include/blessings/linux/ANSI/terminal_io_ansi_linux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/ANSI/
	cp linux/ANSI/ansi_symbol_table.hpp $(HOME)/.prefix/usr/include/blessings/linux/ANSI/ansi_symbol_table.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/ANSI/
	cp linux/ANSI/terminal_io_ansi_linux_impl.hpp $(HOME)/.prefix/usr/include/blessings/linux/ANSI/terminal_io_ansi_linux_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/write_stream_linux.hpp $(HOME)/.prefix/usr/include/blessings/linux/write_stream_linux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/write_stream_linux_impl.hpp $(HOME)/.prefix/usr/include/blessings/linux/write_stream_linux_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp error.hpp $(HOME)/.prefix/usr/include/blessings/error.hpp
	mkdir -p $(HOME)/.prefix/usr/lib/
	cp libblessings_static.a $(HOME)/.prefix/usr/lib/libblessings_static.a
	cp libblessings_shared.so $(HOME)/.prefix/usr/lib/libblessings_shared.so
uninstall:
	rm -rf $(HOME)/.prefix/usr/include/blessings
	rm -f $(HOME)/.prefix/usr/lib/libblessings_static.a
	rm -f $(HOME)/.prefix/usr/lib/libblessings_shared.so
