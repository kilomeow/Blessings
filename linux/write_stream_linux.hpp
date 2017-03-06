#pragma once

#include <cstdio>
#include <string>

#include "../error.hpp"

namespace blessings {
  class WriteStreamLinux {
    FILE* file;

    WriteStreamLinux(const WriteStreamLinux&);
    WriteStreamLinux& operator=(const WriteStreamLinux&);
  public:
    class Error : public BlessingsError {};
    class WriteError : public Error {};

    WriteStreamLinux(FILE* f=stdout) noexcept;

    template <class Symbol>
    void write(const Symbol&);
    void write(char);
    void write(const char*);
    void write(const std::string&);

    void flush();
  };
}
