#pragma once

#include <iostream>

#include "Monitor.hpp"
#include "Symbol.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol, class Property>
  class Monitor<InputSymbol, OutputSymbol, Property>::Error {
  public:
    Error(const char* msg="Unknown monitor error", bool fullOutput=true) {
      std::cerr << "Blessings Monitor error: " << msg << std::endl;

      if(fullOutput) {
        std::cerr << "InputSymbol info: " << InputSymbol::info << std::endl;
        std::cerr << "OutputSymbol info: " << OutputSymbol::info << std::endl;
        std::cerr << "Property info: " << Property::info << std::endl;
      }
    }
  };

  class SymbolUTF8::Error {
  public:
    Error(const char* msg="Unknown SymbolUTF8 error") {
      std::cerr << "SymbolUTF8 error: " << msg << std::endl;
    }
  };
}
