#pragma once

#include <string>
#include <cstdint>

#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class OutputSymbol, class Property>
  class WriteStream {
  public:
    virtual void write(OutputSymbol, Property)=0;

    virtual MonitorResolution getResolution();
  };
}
