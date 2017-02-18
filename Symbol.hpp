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
    enum ColorName {BLACK=0, RED=1, GREEN=2, YELLOW=3, BLUE=4, MAGENTA=5, CYAN=6, WHITE=7};
    ColorName color;

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
  struct PropertyGeneral {
    bool bold;
    bool italics;

    PropertyGeneral() : bold(false), italics(false) {};
  };

  template <class Palette>
  struct Property : public PropertyGeneral {
    Palette color;

    Property() : color(Palette::DefaultColor) {
      PropertyGeneral::PropertyGeneral();
    }
  };

  struct ColorType {
    class Error;

    enum Type {OTHER, RGB, ANSI};

    int type;

    ColorType(Type t);
    ColorType(int t);

    Type getType();
  };
}
