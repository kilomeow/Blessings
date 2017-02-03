#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Symbol.hpp"

namespace Blessings_ns {
  template <class OutputSymbol, class Color>
  class WriteStreamLinux : public WriteStream<OutputStream, Color>;

  template <>
  class WriteStreamLinux<char, ColorANSI> {
    int fd;
  public:
    WriteStreamLinux(const char* path="") {

    }

    void write(char a, ColorANSI color) {

    }
  };
}
