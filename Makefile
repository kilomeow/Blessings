all: build/Symbol/SymbolUTF8.o build/Symbol/SomeUTF8Symbols.o build/Symbol/Symbol.o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o build/ANSILinux/WSL_SymbolUTF8.o build/main.o
	clang -lstdc++ --std=c++1z build/Symbol/SymbolUTF8.o build/Symbol/SomeUTF8Symbols.o build/Symbol/Symbol.o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o build/ANSILinux/WSL_SymbolUTF8.o build/main.o -o work

build/Symbol/SymbolUTF8.o : Symbol/Symbol.hpp Symbol/SymbolUTF8.hpp Symbol/SymbolUTF8.cpp
	mkdir -p build/Symbol/
	clang --std=c++1z -c Symbol/SymbolUTF8.cpp -o build/Symbol/SymbolUTF8.o

build/Symbol/SomeUTF8Symbols.o : Symbol/SymbolUTF8.hpp Symbol/SomeUTF8Symbols.hpp Symbol/SomeUTF8Symbols.cpp
	mkdir -p build/Symbol/
	clang --std=c++1z -c Symbol/SomeUTF8Symbols.cpp -o build/Symbol/SomeUTF8Symbols.o

build/Symbol/Symbol.o : Symbol/Symbol.hpp Symbol/../Error.hpp Symbol/Symbol.cpp
	mkdir -p build/Symbol/
	clang --std=c++1z -c Symbol/Symbol.cpp -o build/Symbol/Symbol.o

build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o : ANSILinux/TIOAL_PropANSI_impl.hpp ANSILinux/../Symbol/Symbol.hpp ANSILinux/../Symbol/SymbolUTF8.hpp ANSILinux/TIOAL_PropANSI_SymbolUTF8.cpp
	mkdir -p build/ANSILinux/
	clang --std=c++1z -c ANSILinux/TIOAL_PropANSI_SymbolUTF8.cpp -o build/ANSILinux/TIOAL_PropANSI_SymbolUTF8.o

build/ANSILinux/WSL_SymbolUTF8.o : ANSILinux/WSL_SymbolUTF8.hpp ANSILinux/../Symbol/SymbolUTF8.hpp ANSILinux/../Error.hpp ANSILinux/WSL_SymbolUTF8.cpp
	mkdir -p build/ANSILinux/
	clang --std=c++1z -c ANSILinux/WSL_SymbolUTF8.cpp -o build/ANSILinux/WSL_SymbolUTF8.o

build/main.o : Symbol/SymbolUTF8.hpp Symbol/Symbol.hpp ANSILinux/TerminalIOANSILinux.hpp main.cpp
	mkdir -p build/ANSILinux/
	clang --std=c++1z -c main.cpp -o build/main.o

clean:
	rm -rf build
