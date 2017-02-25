#pragma once

#include <string>
#include <cstdint>

#include "../Error.hpp"

namespace blessings {
  template <class SymbolType>
  SymbolType readSymbol(FILE*);

  template <class SymbolType>
  void writeSymbol(const SymbolType&, FILE*);


  //Color
  struct ColorANSI {
    enum ColorT {BLACK=0, RED=1, GREEN=2, YELLOW=3, BLUE=4, MAGENTA=5, CYAN=6, WHITE=7};
    ColorT color;

    ColorANSI(ColorT col=BLACK) : color(col) {};

    static ColorANSI DefaultColor;
  };


  struct ColorRGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    class Error : public BlessingsError {};
    class InitError : public Error {};

    ColorRGB(int red=0, int green=0, int blue=0);

    static const ColorRGB WHITE;
    static const ColorRGB BLACK;

    static ColorRGB DefaultColor;
  };


  //Property
  struct Property {
    virtual const Property* getDefault()=0;
  };

  struct PropertyANSI : public Property {
    ColorANSI color;
    ColorANSI backgroundColor;
    bool italics;
    bool bold;

    bool empty;

    static const PropertyANSI defaultProperty;

    virtual const PropertyANSI* getDefault() {
      return &defaultProperty;
    };

    PropertyANSI() : empty(true) {};
  };

  struct PropertyType {
    class Error;
    class InitError;

    enum Type {OTHER=0, ANSI=1};

    int type;

    PropertyType(Type t);
    PropertyType(int t);

    Type getType();
  };


  class PropertyType::Error : public BlessingsError {};
  class PropertyType::InitError : PropertyType::Error {};
}
