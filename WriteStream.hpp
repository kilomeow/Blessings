#pragma once

#include <string>

#include "Symbol.hpp"

namespace Blessings_ns {
  template <class OutputSymbol>
  class WriteStream {
  public:
    virtual void write(OutputSymbol, PropertyGeneral*)=0;
    virtual void write(OutputSymbol)=0;
    virtual void write(char)=0;
    virtual void write(const char*)=0;
    virtual void write(std::string)=0;

    virtual void flush()=0;

    virtual PropertyType getPropertyType()=0;
  };
}
