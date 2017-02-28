#pragma once

#include <cstdio>

#include "../symbol/symbol_utf8.hpp"
#include "../write_stream.hpp"
#include "write_stream_linux.hpp"
#include "../error.hpp"

namespace blessings {
  template <>
  class WriteStreamLinux<SymbolUTF8> :
    public WriteStream<SymbolUTF8> {

    FILE* file;
  public:
    class Error;
    class WriteError;

    WriteStreamLinux(FILE* f=stdout);

    void write(SymbolUTF8);
    void write(char);
    void write(const char*);
    void write(std::string);

    void flush();
  };


  class WriteStreamLinux<SymbolUTF8>::Error : BlessingsError {};
  class WriteStreamLinux<SymbolUTF8>::WriteError :\
    public WriteStreamLinux<SymbolUTF8>::Error {};
}
