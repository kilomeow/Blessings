#include "Symbol.hpp"
#include "../Error.hpp"

namespace blessings {
  ColorANSI ColorANSI::DefaultColor=ColorANSI(BLACK);
  ColorRGB ColorRGB::DefaultColor=ColorRGB::BLACK;

  const ColorRGB ColorRGB::WHITE=ColorRGB(255,255,255);
  const ColorRGB ColorRGB::BLACK=ColorRGB(0,0,0);

  const struct PropertyANSI PropertyANSI::defaultProperty=PropertyANSI();

  ColorRGB::ColorRGB(int red, int green, int blue) : r(red), g(green), b(blue) {
    if(red<0 || red>255 || green<0 || green>255 || blue<0 || blue>255) {
      throw InitError();
    }
  }

  PropertyType::PropertyType(Type t) {
    if(t==OTHER) throw InitError();
    type=t;
  }

  PropertyType::PropertyType(int t) {
    if(t==static_cast<int>(OTHER)) throw InitError();
    type=t;
  }

  PropertyType::Type PropertyType::getType() {
    if(static_cast<Type>(type)==ANSI) {
      return static_cast<Type>(type);
    }
    else return OTHER;
  }
}
