#pragma once

#include "error.hpp"

namespace blessings {
  //Color
  struct ColorANSI {
    class Error : public BlessingsError {};
    class InitError : public Error {};

    enum ColorT {BLACK=0, RED=1, GREEN=2, YELLOW=3, BLUE=4, MAGENTA=5, CYAN=6, WHITE=7, NONE=8};
    ColorT color;

    const static ColorANSI defaultColor;

    ColorANSI(ColorT col) : color(col) {}
    ColorANSI(int c) : color(ColorT(c)) {if(c>8 || c<0) throw InitError();}
    ColorANSI() : color(defaultColor.color) {}

    operator ColorT() {return color;}
  };

  inline bool operator==(const ColorANSI& a, const ColorANSI& b) {
    return a.color==b.color;
  }

  inline bool operator!=(const ColorANSI& a, const ColorANSI& b) {
    return a.color!=b.color;
  }


  //Property
  struct PropertyANSI {
    ColorANSI color;
    ColorANSI backgroundColor;
    bool italics;
    bool bold;

    static const PropertyANSI defaultProperty;

    PropertyANSI() {
      color=defaultProperty.color;
      backgroundColor=defaultProperty.backgroundColor;
      italics=defaultProperty.italics;
      bold=defaultProperty.bold;
    }

    PropertyANSI(ColorANSI clr=ColorANSI::NONE, \
      ColorANSI bgclr=ColorANSI::NONE, bool itl=false, bool bld=false) :
      color(clr), backgroundColor(bgclr), italics(itl), bold(bld) {}
  };

  bool operator==(const PropertyANSI&, const PropertyANSI&);
  bool operator!=(const PropertyANSI&, const PropertyANSI&);
}
