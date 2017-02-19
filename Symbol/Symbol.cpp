#include "Symbol.hpp"
#include "Error.hpp"

namespace Blessings_ns {
  ColorANSI ColorANSI::DefaultColor=ColorANSI(BLACK);
  ColorRGB ColorRGB::DefaultColor=ColorRGB::BLACK;

  PropertyANSI::DefaultProperty={ColorRGB::GREEN, false, false};

  const ColorRGB ColorRGB::WHITE=ColorRGB(255,255,255);
  const ColorRGB ColorRGB::BLACK=ColorRGB(0,0,0);

  ColorRGB::ColorRGB(int red, int green, int blue) : r(red), g(green), b(blue) {
    if(red<0 || red>255 || green<0 || green>255 || blue<0 || blue>255) {
      throw InitError(1, "bad init values");
    }
  }

  PropertyType::PropertyType(Type t) {
    if(t==OTHER) throw InitError(1, "bad init Type");
    type=t;
  }

  PropertyType::PropertyType(int t) {
    if(t==static_cast<int>(OTHER)) throw InitError(2, "init int equals to OTHER");
    type=t;
  }

  PropertyType::Type PropertyType::getType() {
    if(static_cast<Type>(type)==ANSI) {
      return static_cast<Type>(type);
    }
    else return OTHER;
  }
}
