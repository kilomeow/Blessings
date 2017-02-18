#pragma once

#include <iostream>

#include "Monitor.hpp"
#include "Symbol.hpp"
#include "SymbolUTF8.hpp"
#include "WSAL/WSAL_DefaultProp_SymbolUTF8.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol>
  class Monitor<InputSymbol, OutputSymbol>::Error {
  public:
    Error(const char* msg="unknown monitor error") {
      std::cerr << "Blessings Monitor error: " << msg << std::endl;
    }
  };

  class SymbolUTF8::Error {
  public:
    Error(const char* msg="unknown SymbolUTF8 error") {
      std::cerr << "SymbolUTF8 error: " << msg << std::endl;
    }
  };

  class ColorType::Error {
  public:
    Error(const char* msg="unknown ColorType error") {
      std::cerr << "ColorType error: " << msg << std::endl;
    }
  };

  class ColorRGB::Error {
  public:
    Error(const char* msg="unknown ColorRGB error") {
      std::cerr << "ColorRGB error: " << msg << std::endl;
    }
  };

  class WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> >::Error {
  public:
    Error(const char* msg="unknown WriteStreamANSILinux<SymbolUTF8, \
      Property<ColorANSI> > error") {
      std::cerr << "WriteStreamANSILinux<SymbolUTF8, Property<ColorANSI> > \
        error: " << msg << std::endl;
    }
  };
}
