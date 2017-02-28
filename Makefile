lib: lib_shared lib_static
build/ansilinux/symbolutf8.o: \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/symbolutf8.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/writestream.hpp
	mkdir -p build/ansilinux/
	g++ --std=c++11 -fpic -c -o build/ansilinux/symbolutf8.o ansilinux/symbolutf8.cpp
build/ansilinux/propertyutf8.o: \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/propertyutf8.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/property.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/utf8symbols.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/property.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../readstream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../astructs.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/symbolutf8.hpp
	mkdir -p build/ansilinux/
	g++ --std=c++11 -fpic -c -o build/ansilinux/propertyutf8.o ansilinux/propertyutf8.cpp
build/ansilinux/property.o: \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/property.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/utf8symbols.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/property.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../readstream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../astructs.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/symbolutf8.hpp
	mkdir -p build/ansilinux/
	g++ --std=c++11 -fpic -c -o build/ansilinux/property.o ansilinux/property.cpp
build/test.o: /media/sf_HOME/Dest/Projects/Blessings/test.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/property.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../readstream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../astructs.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/ansilinux/../terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/monitor.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/monitor.hpp
	mkdir -p build/
	g++ --std=c++11 -fpic -c -o build/test.o test.cpp
build/symbol/symbolutf8.o: \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbolutf8.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbolutf8.hpp
	mkdir -p build/symbol/
	g++ --std=c++11 -fpic -c -o build/symbol/symbolutf8.o symbol/symbolutf8.cpp
build/symbol/utf8symbols.o: \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/utf8symbols.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbolutf8.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/utf8symbols.hpp
	mkdir -p build/symbol/
	g++ --std=c++11 -fpic -c -o build/symbol/utf8symbols.o symbol/utf8symbols.cpp
build/symbol/symbol.o: \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/../error.hpp
	mkdir -p build/symbol/
	g++ --std=c++11 -fpic -c -o build/symbol/symbol.o symbol/symbol.cpp
build/monitor.o: /media/sf_HOME/Dest/Projects/Blessings/monitor.cpp \
 /media/sf_HOME/Dest/Projects/Blessings/monitor.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/astructs.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/terminalio.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/symbol.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/symbol/../error.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/writestream.hpp \
 /media/sf_HOME/Dest/Projects/Blessings/readstream.hpp
	mkdir -p build/
	g++ --std=c++11 -fpic -c -o build/monitor.o monitor.cpp
lib_static: build/ansilinux/symbolutf8.o build/ansilinux/propertyutf8.o build/ansilinux/property.o build/test.o build/symbol/symbolutf8.o build/symbol/utf8symbols.o build/symbol/symbol.o build/monitor.o
	ar rcs blessings.a $^
lib_shared: build/ansilinux/symbolutf8.o build/ansilinux/propertyutf8.o build/ansilinux/property.o build/test.o build/symbol/symbolutf8.o build/symbol/utf8symbols.o build/symbol/symbol.o build/monitor.o
	g++ --std=c++11 -shared -o blessings.so $^
test: build/ansilinux/symbolutf8.o build/ansilinux/propertyutf8.o build/ansilinux/property.o build/test.o build/symbol/symbolutf8.o build/symbol/utf8symbols.o build/symbol/symbol.o build/monitor.o
	g++ --std=c++11  -o work -lstdc++ $^
clean:
	rm -rf build
	rm -f work
	rm -f blessings.a
	rm -f blessings.so
install:
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp error.hpp $(HOME)/.prefix/usr/include/blessings/error.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp astructs.hpp $(HOME)/.prefix/usr/include/blessings/astructs.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ansilinux/
	cp ansilinux/terminalio.hpp $(HOME)/.prefix/usr/include/blessings/ansilinux/terminalio.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ansilinux/
	cp ansilinux/symbolutf8.hpp $(HOME)/.prefix/usr/include/blessings/ansilinux/symbolutf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ansilinux/
	cp ansilinux/property.hpp $(HOME)/.prefix/usr/include/blessings/ansilinux/property.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ansilinux/
	cp ansilinux/writestream.hpp $(HOME)/.prefix/usr/include/blessings/ansilinux/writestream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp writestream.hpp $(HOME)/.prefix/usr/include/blessings/writestream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp readstream.hpp $(HOME)/.prefix/usr/include/blessings/readstream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/symbolutf8.hpp $(HOME)/.prefix/usr/include/blessings/symbol/symbolutf8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/symbol.hpp $(HOME)/.prefix/usr/include/blessings/symbol/symbol.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/symbol/
	cp symbol/utf8symbols.hpp $(HOME)/.prefix/usr/include/blessings/symbol/utf8symbols.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp monitor.hpp $(HOME)/.prefix/usr/include/blessings/monitor.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp terminalio.hpp $(HOME)/.prefix/usr/include/blessings/terminalio.hpp
	mkdir -p $(HOME)/.prefix/usr/lib/
	cp blessings.a $(HOME)/.prefix/usr/lib/blessings.a
	cp blessings.so $(HOME)/.prefix/usr/lib/blessings.so
uninstall:
	rm -rf $(HOME)/.prefix/usr/include/blessings
	rm -f $(HOME)/.prefix/usr/lib/blessings.a
	rm -f $(HOME)/.prefix/usr/lib/blessings.so
