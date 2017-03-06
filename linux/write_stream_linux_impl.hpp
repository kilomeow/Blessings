#pragma once

#include "write_stream_linux.hpp"

namespace blessings {
  template <class Symbol>
  void WriteStreamLinux::write(const Symbol& sym) {
    try {
      sym.writeToFile(file);
    }
    catch (...) {
      throw WriteError();
    }
  }
}
