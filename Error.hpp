#pragma once

#include <iostream>
#include <string>

#include "Monitor.hpp"
#include "Symbol/Symbol.hpp"
#include "Symbol/SymbolUTF8.hpp"
#include "WSAL/WSAL_DefaultProp_SymbolUTF8.hpp"

namespace Blessings_ns {
  template <class InputSymbol, class OutputSymbol>
  class Monitor<InputSymbol, OutputSymbol>::Error {
  public:
    Error(const char* msg="unknown monitor error") {
      std::cerr << "Blessings Monitor error: " << msg << std::endl;
    }
  };


  //SymbolUTF8
  class SymbolUTF8::Error {
  public:
    std::string msg;
    int type;

    Error(int t, std::string m="unknown SymbolUTF8 error"s) : type(t), msg(m) {};
    printError() {std::cerr << msg << std::endl};
  };


  class SymbolUTF8::IOError : public SymbolUTF8::Error {
  public:
    Error(int t, std::string m="unknown SymbolUTF8 IO error"s) : type(t), msg(m) {};
    printError() {std::cerr << msg << std::endl};
  };


  class SymbolUTF8::InitError : public SymbolUTF8::Error {
  public:
    Error(int t, std::string m="unknown SymbolUTF8 init error"s) : type(t), msg(m) {};
    printError() {std::cerr << msg << std::endl};
  };


  //ColoType
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
