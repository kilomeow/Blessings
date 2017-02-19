#pragma once

#include <string>

namespace Blessings {
  template <class OutputSymbol>
  class WriteStream {
  public:
    virtual void write(OutputSymbol)=0;
    virtual void write(char)=0;
    virtual void write(const char*)=0;
    virtual void write(std::string)=0;

    virtual void flush()=0;
  };
}
