#include <cstdio>
#include <cstring>
#include <string>

#include "WSL_SymbolUTF8.hpp"
#include "../Symbol/SymbolUTF8.hpp"
#include "../Error.hpp"

namespace blessings {
  WriteStreamLinux<SymbolUTF8>::WriteStreamLinux(FILE* f) :\
    file(f) {};

  void WriteStreamLinux<SymbolUTF8>::write(SymbolUTF8 sym) {
    try {
      writeSymbol(sym, file);
    }
    catch(...) {
      throw WriteError();
    }
  }

  void WriteStreamLinux<SymbolUTF8>::write(char c) {
    int temp=fputc(c, file);
    if(temp==EOF) throw WriteError();
  }

  void WriteStreamLinux<SymbolUTF8>::write(const char* str) {
    int len=strlen(str);
    for(int i=0; i<len; ++i) {
      int temp=fputc(str[i], file);
      if(temp==EOF) throw WriteError();
    }
  }

  void WriteStreamLinux<SymbolUTF8>::write(std::string str) {
    for(int i=0; i<str.size(); ++i) {
      int temp=fputc(str[i], file);
      if(temp==EOF) throw WriteError();
    }
  }

  void WriteStreamLinux<SymbolUTF8>::flush() {
    int temp=fflush(file);
    if(temp==EOF) throw WriteError();
  }
}
