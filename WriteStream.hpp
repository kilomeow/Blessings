#pragma once

#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class OutputSymbol, class Property>
  class WriteStream {
  public:
    virtual const static info;

    virtual void write(OutputSymbol, Property)=0;

    virtual MonitorResolution getResolution();
  };
}
