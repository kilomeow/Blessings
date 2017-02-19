#pragma once

#include <string>
#include <cstdint>

namespace Blessings_ns {
  class Symbol {
  public:
    virtual std::string getString() const=0;
  };

  template <class SymbolType>
  SymbolType getSym(FILE*);

  //Color
  struct ColorANSI {
    enum ColorT {BLACK=0, RED=1, GREEN=2, YELLOW=3, BLUE=4, MAGENTA=5, CYAN=6, WHITE=7};
    ColorT color;

    ColorANSI(ColorName col=BLACK) : color(col) {};

    static ColorANSI DefaultColor;
  };

  struct ColorRGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    class Error;

    ColorRGB(int red=0, int green=0, int blue=0);

    static const ColorRGB WHITE;
    static const ColorRGB BLACK;

    static ColorRGB DefaultColor;
  };

  //Property
  struct PropertyGeneral {};

  struct PropertyANSI : public PropertyGeneral {
    ColorANSI color;
    bool italics;
    bool bold;

    static PropertyANSI DefaultProperty;

    Property() {
      *this=DefaultProperty;
    }
  };

  struct PropertyType {
    class Error;

    enum Type {OTHER, ANSI};

    int type;

    PropertyType(Type t);
    PropertyType(int t);

    Type getType();
  };
}
