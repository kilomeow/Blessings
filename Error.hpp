#pragma once

#include <iostream>

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol, class Property>
  class Monitor::Error {
  public:
    MonitorError(const char* msg="Unknown monitor error", bool fullOutput=true) {
      std::cerr << "Blessings Monitor error: " << msg << std::endl;

      if(fullOutput) {
        std::cerr << "InputSymbol info: " << InputSymbol::info << std::endl;
        std::cerr << "OutputSymbol info: " << OutputSymbol::info << std::endl;
        std::cerr << "Property info: " << Property::info << std::endl;
      }
    }
  };
}
