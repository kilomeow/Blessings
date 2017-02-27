#pragma once

#include <string>
#include <cstdint>
#include <utility>

#include "../Error.hpp"

namespace blessings {
  template <class SymbolType>
  SymbolType readSymbol(FILE*);

  template <class SymbolType>
  void writeSymbol(const SymbolType&, FILE*);

  template <class SymbolType>
  std::pair<SymbolType, const char*> getSymbol(const char* str);
  template <class SymbolType>
  std::pair<SymbolType, const char*> getSymbol(const char* str, size_t n);


  //Color
  struct ColorANSI {
    enum ColorT {BLACK=0, RED=1, GREEN=2, YELLOW=3, BLUE=4, MAGENTA=5, CYAN=6, WHITE=7, NONE=8};
    ColorT color;

    ColorANSI(ColorT col=BLACK) : color(col) {}
    ColorANSI(int c) : color(ColorT(c)) {}

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
  struct Property {};

  struct PropertyANSI : public Property {
    ColorANSI color;
    ColorANSI backgroundColor;
    bool italics;
    bool bold;

    static const PropertyANSI defaultProperty;

    PropertyANSI(ColorANSI clr=ColorANSI::NONE, \
      ColorANSI bgclr=ColorANSI::NONE, bool itl=false, bool bld=false) :
      color(clr), backgroundColor(bgclr), italics(itl), bold(bld) {}
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
