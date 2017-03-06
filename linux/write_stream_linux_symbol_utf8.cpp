#include <cstdio>
#include <cstring>
#include <string>

#include "write_stream_linux_symbol_utf8.hpp"

namespace blessings {
  WriteStreamLinux::WriteStreamLinux(FILE* f) noexcept :\
    file(f) {};
  
  template <class Symbol>
  void WriteStreamLinux::write(const Symbol& sym) {
    try {
      sym.writeToFile(file);
    }
    catch (...) {
      throw WriteError();
    }
  }
  
  template 
  void WriteStreamLinux::write(char c) {
    int temp=fputc(c, file);
    if (temp==EOF) throw WriteError();
  }

  void WriteStreamLinux::write(const char* str) {
    size_t len=strlen(str);
    for (size_t i=0; i<len; ++i) {
      int temp=fputc(str[i], file);
      if (temp==EOF) throw WriteError();
    }
  }

  void WriteStreamLinux::write(std::string str) {
    for (size_t i=0; i<str.size(); ++i) {
      int temp=fputc(str[i], file);
      if (temp==EOF) throw WriteError();
    }
  }

  void WriteStreamLinux::flush() {
    int temp=fflush(file);
    if (temp==EOF) throw WriteError();
  }
}
