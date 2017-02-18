#include "Symbol.hpp"
#include "Error.hpp"

namespace Blessings_ns {
  ColorANSI ColorANSI::DefaultColor=ColorANSI(BLACK);
  ColorRGB ColorRGB::DefaultColor=ColorRGB::BLACK;

  const ColorRGB ColorRGB::WHITE=ColorRGB(255,255,255);
  const ColorRGB ColorRGB::BLACK=ColorRGB(0,0,0);

  ColorRGB::ColorRGB(int red, int green, int blue) : r(red), g(green), b(blue) {
    if(red<0 || red>255 || green<0 || green>255 || blue<0 || blue>255) {
      throw Error("bad init values");
    }
  }

  ColorType::ColorType(Type t) {
    if(t==OTHER) throw Error("bad init Type");
    type=t;
  }

  ColorType::ColorType(int t) {
    if(t==static_cast<int>(OTHER)) throw Error("init int equals to OTHER");
    type=t;
  }

  ColorType::Type ColorType::getType() {
    if(static_cast<Type>(type)==RGB || static_cast<Type>(type)==ANSI) {
      return static_cast<Type>(type);
    }
    else return OTHER;
  }
}
