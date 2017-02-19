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
    void printError() {std::cerr << msg << std::endl};
  };


  class SymbolUTF8::IOError : public SymbolUTF8::Error {
  public:
    IOError(int t, std::string m="unknown SymbolUTF8 IO error"s) :\
      type(t), msg(m) {};
  };


  class SymbolUTF8::InitError : public SymbolUTF8::Error {
  public:
    InitError(int t, std::string m="unknown SymbolUTF8 init error"s) :\
      type(t), msg(m) {};
  };


  class SymbolUTF8::AccessError : public SymbolUTF8::Error {
  public:
    AccessError(int t, std::string m="unknown SymbolUTF8 access error"s) :\
      type(t), msg(m) {};
  };


  //PropertyType
  class PropertyType::Error {
  public:
    std::string msg;
    int type;

    Error(int t, std::string m="unknown PropertyType error"s) : type(t), msg(m) {};
    void printError() {std::cerr << msg << std::endl};
  };


  class PropertyType::InitError : PropertyType::Error {
  public:
    InitError(int t, std::string m="unknown PropertyType init error"s) : type(t), msg(m) {};
  };


  //ColorRGB
  class ColorRGB::Error {
  public:
    std::string msg;
    int type;

    Error(int t, std::string m="unknown ColorRGB error"s) : type(t), msg(m) {};
    void printError() {std::cerr << msg << std::endl};
  };


  class ColorRGB::InitError : public ColorRGB::Error {
  public:
    InitError(int t, std::string m="unknown ColorRGB init error"s) :\
      type(t), msg(m) {};
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
