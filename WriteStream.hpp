#pragma once

#include <string>
#include <cstdint>

#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class OutputSymbol, class Property>
  class WriteStream {
  public:
    virtual void print(OutputSymbol, Property)=0;
    virtual void clearScreen()=0;
    virtual void newLine()=0;
    virtual void moveCursor(uint32_t new_x, uint32_t new_y)=0;
    virtual MonitorResolution getResolution()=0;
  };
}