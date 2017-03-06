#include <cstdio>
#include <cstring>
#include <string>

#include "write_stream_linux.hpp"

namespace blessings {
  WriteStreamLinux::WriteStreamLinux(FILE* f) noexcept :\
    file(f) {};

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

  void WriteStreamLinux::write(const std::string& str) {
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
