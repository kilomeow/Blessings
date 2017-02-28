lib: lib_shared lib_static
build/symbol/some_symbol_utf8_symbols.o: \
 /home/shkiper/Код/Blessings/symbol/some_symbol_utf8_symbols.cpp \
 /home/shkiper/Код/Blessings/symbol/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/symbol/../error.hpp \
 /home/shkiper/Код/Blessings/symbol/some_symbol_utf8_symbols.hpp
	mkdir -p build/symbol/
	clang --std=c++11 -fpic -c -o build/symbol/some_symbol_utf8_symbols.o symbol/some_symbol_utf8_symbols.cpp
build/symbol/symbol_utf8.o: \
 /home/shkiper/Код/Blessings/symbol/symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/symbol/../error.hpp \
 /home/shkiper/Код/Blessings/symbol/symbol_utf8.hpp
	mkdir -p build/symbol/
	clang --std=c++11 -fpic -c -o build/symbol/symbol_utf8.o symbol/symbol_utf8.cpp
build/symbol/symbol.o: /home/shkiper/Код/Blessings/symbol/symbol.cpp \
 /home/shkiper/Код/Blessings/symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/symbol/../error.hpp
	mkdir -p build/symbol/
	clang --std=c++11 -fpic -c -o build/symbol/symbol.o symbol/symbol.cpp
build/monitor_symbol_utf8_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/monitor_symbol_utf8_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/monitor_impl.hpp \
 /home/shkiper/Код/Blessings/monitor.hpp \
 /home/shkiper/Код/Blessings/additional_structs.hpp \
 /home/shkiper/Код/Blessings/terminal_io.hpp \
 /home/shkiper/Код/Blessings/symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/symbol/../error.hpp \
 /home/shkiper/Код/Blessings/write_stream.hpp \
 /home/shkiper/Код/Blessings/read_stream.hpp \
 /home/shkiper/Код/Blessings/symbol/symbol_utf8.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/monitor_symbol_utf8_symbol_utf8.o monitor_symbol_utf8_symbol_utf8.cpp
build/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux_property_ansi_impl.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/some_symbol_utf8_symbols.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/../error.hpp \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux_property_ansi.hpp \
 /home/shkiper/Код/Blessings/linux/../write_stream.hpp \
 /home/shkiper/Код/Blessings/linux/../read_stream.hpp \
 /home/shkiper/Код/Blessings/linux/../additional_structs.hpp \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux.hpp \
 /home/shkiper/Код/Blessings/linux/../terminal_io.hpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux_symbol_utf8.hpp
	mkdir -p build/linux/
	clang --std=c++11 -fpic -c -o build/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.o linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.cpp
build/linux/write_stream_linux_symbol_utf8.o: \
 /home/shkiper/Код/Blessings/linux/write_stream_linux_symbol_utf8.cpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux_symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/../error.hpp \
 /home/shkiper/Код/Blessings/linux/../write_stream.hpp \
 /home/shkiper/Код/Blessings/linux/write_stream_linux.hpp \
 /home/shkiper/Код/Blessings/linux/../symbol/some_symbol_utf8_symbols.hpp
	mkdir -p build/linux/
	clang --std=c++11 -fpic -c -o build/linux/write_stream_linux_symbol_utf8.o linux/write_stream_linux_symbol_utf8.cpp
build/test.o: /home/shkiper/Код/Blessings/test.cpp \
 /home/shkiper/Код/Blessings/symbol/symbol_utf8.hpp \
 /home/shkiper/Код/Blessings/symbol/symbol.hpp \
 /home/shkiper/Код/Blessings/symbol/../error.hpp \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux.hpp \
 /home/shkiper/Код/Blessings/linux/terminal_io_ansi_linux_property_ansi.hpp \
 /home/shkiper/Код/Blessings/linux/../write_stream.hpp \
 /home/shkiper/Код/Blessings/linux/../read_stream.hpp \
 /home/shkiper/Код/Blessings/linux/../additional_structs.hpp \
 /home/shkiper/Код/Blessings/linux/../terminal_io.hpp \
 /home/shkiper/Код/Blessings/monitor.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/test.o test.cpp
lib_static: build/symbol/some_symbol_utf8_symbols.o build/symbol/symbol_utf8.o build/symbol/symbol.o build/monitor_symbol_utf8_symbol_utf8.o build/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.o build/linux/write_stream_linux_symbol_utf8.o build/test.o
	ar rcs blessings.a $^
lib_shared: build/symbol/some_symbol_utf8_symbols.o build/symbol/symbol_utf8.o build/symbol/symbol.o build/monitor_symbol_utf8_symbol_utf8.o build/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.o build/linux/write_stream_linux_symbol_utf8.o build/test.o
	clang --std=c++11 -shared -o blessings.so $^
test: build/symbol/some_symbol_utf8_symbols.o build/symbol/symbol_utf8.o build/symbol/symbol.o build/monitor_symbol_utf8_symbol_utf8.o build/linux/terminal_io_ansi_linux_property_ansi_symbol_utf8.o build/linux/write_stream_linux_symbol_utf8.o build/test.o
	clang --std=c++11 -o work -lstdc++ $^
clean:
	rm -rf build
	rm -f work
	rm -f blessings.a
	rm -f blessings.so
install:
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp read_stream.hpp $(HOME)/.prefix/usr/include/blessings/read_stream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp write_stream.hpp $(HOME)/.prefix/usr/include/blessings/write_stream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp monitor_impl.hpp $(HOME)/.prefix/usr/include/blessings/monitor_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/symbol.hpp $(HOME)/.prefix/usr/include/blessings/symbol/symbol.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/some_symbol_utf8_symbols.hpp $(HOME)/.prefix/usr/include/blessings/symbol/some_symbol_utf8_symbols.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/symbol_utf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol/symbol_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp terminal_io.hpp $(HOME)/.prefix/usr/include/blessings/terminal_io.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp monitor.hpp $(HOME)/.prefix/usr/include/blessings/monitor.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp additional_structs.hpp $(HOME)/.prefix/usr/include/blessings/additional_structs.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/terminal_io_ansi_linux.hpp $(HOME)/.prefix/usr/include/blessings/linux/terminal_io_ansi_linux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/terminal_io_ansi_linux_property_ansi.hpp $(HOME)/.prefix/usr/include/blessings/linux/terminal_io_ansi_linux_property_ansi.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/write_stream_linux.hpp $(HOME)/.prefix/usr/include/blessings/linux/write_stream_linux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/write_stream_linux_symbol_utf8.hpp $(HOME)/.prefix/usr/include/blessings/linux/write_stream_linux_symbol_utf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/linux/
	cp linux/terminal_io_ansi_linux_property_ansi_impl.hpp $(HOME)/.prefix/usr/include/blessings/linux/terminal_io_ansi_linux_property_ansi_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp error.hpp $(HOME)/.prefix/usr/include/blessings/error.hpp
	mkdir -p $(HOME)/.prefix/usr/lib/
	cp blessings.a $(HOME)/.prefix/usr/lib/blessings.a
	cp blessings.so $(HOME)/.prefix/usr/lib/blessings.so
uninstall:
	rm -rf $(HOME)/.prefix/usr/include/blessings
	rm -f $(HOME)/.prefix/usr/lib/blessings.a
	rm -f $(HOME)/.prefix/usr/lib/blessings.so
