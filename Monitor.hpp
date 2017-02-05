#pragma once

#include <cstdint>
#include <utility>

#include "AdditionalStructs.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol, class Property>
  class Monitor {
    //Ram fills realization.
  public:
    Monitor(ReadStream* RS, WriteStream* WS, MonitorResolution res);
      //If res.x_size==0 and res.y_size==0 - Resolution=WS->getResolution()
      //If res.x_size==0 but res.y_size!=0 or res.x_size!=0 but res.y_size==0 - throw exception

    Monitor(const Monitor&); //If needed or remove
    Monitor& operator=(const Monitor&) //If needed or remove

    ~Monitor() //If needed or remove

    class Error;

    std::pair<OutputSymbol, Property>& operator(uint32_t x, uint32_t y);
    std::pair<OutputSymbol, Property> operator(uint32_t x, uint32_t y) const;

    void printToTerm();
    InputSymbol getSym();
  };

}
