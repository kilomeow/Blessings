#pragma once

#include <string>
#include <cstdint>
#include <utility>

#include "../error.hpp"

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

    ColorANSI(ColorT col=NONE) : color(col) {}
    ColorANSI(int c) : color(ColorT(c)) {}

    operator ColorT() {return color;}

    const static ColorANSI DefaultColor;
  };

  inline bool operator==(const ColorANSI& a, const ColorANSI& b) {
    return a.color==b.color;
  }

  inline bool operator!=(const ColorANSI& a, const ColorANSI& b) {
    return a.color!=b.color;
  }


  //Property
  struct Property {
    virtual bool compare(const Property*)=0 const;
  };

  struct PropertyANSI : public Property {
    ColorANSI color;
    ColorANSI backgroundColor;
    bool italics;
    bool bold;

    bool compare(const Property*) const;
    static const PropertyANSI defaultProperty;

    PropertyANSI(ColorANSI clr=ColorANSI::NONE, \
      ColorANSI bgclr=ColorANSI::NONE, bool itl=false, bool bld=false) :
      color(clr), backgroundColor(bgclr), italics(itl), bold(bld) {}
  };

  bool operator==(const PropertyANSI&, const PropertyANSI&);
  bool operator!=(const PropertyANSI&, const PropertyANSI&);

  inline bool PropertyANSI::compare(const Property* prop) const {
    return *this==*static_cast<const PropertyANSI*>(prop);
  }

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
