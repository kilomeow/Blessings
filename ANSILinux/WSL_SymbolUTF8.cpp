#include <cstdio>

#include "WSL_SymbolUTF8.hpp"
#include "../Symbol/SymbolUTF8.hpp"
#include "../Error.hpp"

namespace Blessings {
  WriteStreamLinux<SymbolUTF8>::WriteStreamLinux(FILE* f) :\
    file(f) {};

  void WriteStreamLinux<SymbolUTF8>::write(SymbolUTF8 sym) {
    try {
      sym.writeToFile(file);
    }
    catch(...) {
      throw WriteError();
    }
  }

  void WriteStreamLinux<SymbolUTF8>::write(char c) {
    int temp=fputc(c, file);
    if(temp==EOF) throw WriteError();
  }

  void WriteStreamLinux<SymbolUTF8>::flush() {
    int temp=fflush(file);
    if(temp==EOF) throw WriteError();
  }
}
