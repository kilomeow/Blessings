lib: lib_shared lib_static
build/Monitor.o: /home/shkiper/Код/Blessings/Monitor.cpp \
 /home/shkiper/Код/Blessings/Monitor.hpp \
 /home/shkiper/Код/Blessings/AdditionalStructs.hpp \
 /home/shkiper/Код/Blessings/TerminalIO.hpp \
 /home/shkiper/Код/Blessings/Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/WriteStream.hpp \
 /home/shkiper/Код/Blessings/ReadStream.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/Monitor.o Monitor.cpp
build/Symbol/SymbolUTF8.o: \
 /home/shkiper/Код/Blessings/Symbol/SymbolUTF8.cpp \
 /home/shkiper/Код/Blessings/Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/Symbol/SymbolUTF8.hpp
	mkdir -p build/Symbol/
	clang --std=c++11 -fpic -c -o build/Symbol/SymbolUTF8.o Symbol/SymbolUTF8.cpp
build/Symbol/SomeUTF8Symbols.o: \
 /home/shkiper/Код/Blessings/Symbol/SomeUTF8Symbols.cpp \
 /home/shkiper/Код/Blessings/Symbol/SymbolUTF8.hpp \
 /home/shkiper/Код/Blessings/Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/Symbol/SomeUTF8Symbols.hpp
	mkdir -p build/Symbol/
	clang --std=c++11 -fpic -c -o build/Symbol/SomeUTF8Symbols.o Symbol/SomeUTF8Symbols.cpp
build/Symbol/Symbol.o: /home/shkiper/Код/Blessings/Symbol/Symbol.cpp \
 /home/shkiper/Код/Blessings/Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/Symbol/../Error.hpp
	mkdir -p build/Symbol/
	clang --std=c++11 -fpic -c -o build/Symbol/Symbol.o Symbol/Symbol.cpp
build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o: \
 /home/shkiper/Код/Blessings/ANSILinux/TIOAL_PropANSI_SymbolUTF8.cpp \
 /home/shkiper/Код/Blessings/ANSILinux/TIOAL_PropANSI_impl.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/SomeUTF8Symbols.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/SymbolUTF8.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/TIOAL_PropANSI.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../WriteStream.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../ReadStream.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../AdditionalStructs.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/TerminalIOANSILinux.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../TerminalIO.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/WriteStreamLinux.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/WSL_SymbolUTF8.hpp
	mkdir -p build/ANSILinux/
	clang --std=c++11 -fpic -c -o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o ANSILinux/TIOAL_PropANSI_SymbolUTF8.cpp
build/ANSILinux/WSL_SymbolUTF8.o: \
 /home/shkiper/Код/Blessings/ANSILinux/WSL_SymbolUTF8.cpp \
 /home/shkiper/Код/Blessings/ANSILinux/WSL_SymbolUTF8.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/SymbolUTF8.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../WriteStream.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/WriteStreamLinux.hpp
	mkdir -p build/ANSILinux/
	clang --std=c++11 -fpic -c -o build/ANSILinux/WSL_SymbolUTF8.o ANSILinux/WSL_SymbolUTF8.cpp
build/test.o: /home/shkiper/Код/Blessings/test.cpp \
 /home/shkiper/Код/Blessings/Symbol/SymbolUTF8.hpp \
 /home/shkiper/Код/Blessings/Symbol/Symbol.hpp \
 /home/shkiper/Код/Blessings/Symbol/../Error.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/TerminalIOANSILinux.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/TIOAL_PropANSI.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../WriteStream.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../ReadStream.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../AdditionalStructs.hpp \
 /home/shkiper/Код/Blessings/ANSILinux/../TerminalIO.hpp \
 /home/shkiper/Код/Blessings/Monitor.cpp \
 /home/shkiper/Код/Blessings/Monitor.hpp
	mkdir -p build/
	clang --std=c++11 -fpic -c -o build/test.o test.cpp
lib_static: build/Monitor.o build/Symbol/SymbolUTF8.o build/Symbol/SomeUTF8Symbols.o build/Symbol/Symbol.o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o build/ANSILinux/WSL_SymbolUTF8.o build/test.o
	ar rcs blessings.a $^
lib_shared: build/Monitor.o build/Symbol/SymbolUTF8.o build/Symbol/SomeUTF8Symbols.o build/Symbol/Symbol.o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o build/ANSILinux/WSL_SymbolUTF8.o build/test.o
	clang --std=c++11 -shared -o blessings.so $^
test: build/Monitor.o build/Symbol/SymbolUTF8.o build/Symbol/SomeUTF8Symbols.o build/Symbol/Symbol.o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o build/ANSILinux/WSL_SymbolUTF8.o build/test.o
	clang --std=c++11 -o work -lstdc++ $^
clean:
	rm -rf build
	rm -f work
	rm -f blessings.a
	rm -f blessings.so
install:
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp TerminalIO.hpp $(HOME)/.prefix/usr/include/blessings/TerminalIO.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp ReadStream.hpp $(HOME)/.prefix/usr/include/blessings/ReadStream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp WriteStream.hpp $(HOME)/.prefix/usr/include/blessings/WriteStream.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/Symbol/
	cp Symbol/Symbol.hpp $(HOME)/.prefix/usr/include/blessings/Symbol/Symbol.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/Symbol/
	cp Symbol/SymbolUTF8.hpp $(HOME)/.prefix/usr/include/blessings/Symbol/SymbolUTF8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/Symbol/
	cp Symbol/SomeUTF8Symbols.hpp $(HOME)/.prefix/usr/include/blessings/Symbol/SomeUTF8Symbols.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ANSILinux/
	cp ANSILinux/TIOAL_PropANSI_impl.hpp $(HOME)/.prefix/usr/include/blessings/ANSILinux/TIOAL_PropANSI_impl.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ANSILinux/
	cp ANSILinux/TIOAL_PropANSI.hpp $(HOME)/.prefix/usr/include/blessings/ANSILinux/TIOAL_PropANSI.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ANSILinux/
	cp ANSILinux/TerminalIOANSILinux.hpp $(HOME)/.prefix/usr/include/blessings/ANSILinux/TerminalIOANSILinux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ANSILinux/
	cp ANSILinux/WSL_SymbolUTF8.hpp $(HOME)/.prefix/usr/include/blessings/ANSILinux/WSL_SymbolUTF8.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/ANSILinux/
	cp ANSILinux/WriteStreamLinux.hpp $(HOME)/.prefix/usr/include/blessings/ANSILinux/WriteStreamLinux.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp Error.hpp $(HOME)/.prefix/usr/include/blessings/Error.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp Monitor.hpp $(HOME)/.prefix/usr/include/blessings/Monitor.hpp
	mkdir -p $(HOME)/.prefix/usr/include/blessings/
	cp AdditionalStructs.hpp $(HOME)/.prefix/usr/include/blessings/AdditionalStructs.hpp
	mkdir -p $(HOME)/.prefix/usr/lib/
	cp blessings.a $(HOME)/.prefix/usr/lib/blessings.a
	cp blessings.so $(HOME)/.prefix/usr/lib/blessings.so
uninstall:
	rm -rf $(HOME)/.prefix/usr/include/blessings
	rm -f $(HOME)/.prefix/usr/lib/blessings.a
	rm -f $(HOME)/.prefix/usr/lib/blessings.so
