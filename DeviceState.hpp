#pragma once

#include "WriteStream.hpp"
#include "ReadStream.hpp"
#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol, class Property>
  class DeviceState {
  public:
    virtual MonitorResolution getResolution getResolution(\
      ReadStream<InputSymbol>*, WriteStream<OutputSymbol, Property>*)=0;
    virtual GridPos getCursorPos(\
      ReadStream<InputSymbol>*, WriteStream<OutputSymbol, Property>*)=0;
  };
}
