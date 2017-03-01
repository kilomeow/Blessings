#include "symbol.hpp"
#include "../error.hpp"

namespace blessings {
  const ColorANSI ColorANSI::DefaultColor=ColorANSI(NONE);

  const struct PropertyANSI PropertyANSI::defaultProperty=PropertyANSI();

  bool operator==(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics==b.italics && b.bold==b.bold && a.color==b.color && \
      a.backgroundColor==b.backgroundColor;
  }

  bool operator!=(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics!=b.italics || b.bold!=b.bold || a.color!=b.color || \
      a.backgroundColor!=b.backgroundColor;
  }

  PropertyType::PropertyType(Type t) {
    if (t==OTHER) throw InitError();
    type=t;
  }

  PropertyType::PropertyType(int t) {
    if (t==static_cast<int>(OTHER)) throw InitError();
    type=t;
  }

  PropertyType::Type PropertyType::getType() {
    if (static_cast<Type>(type)==ANSI) {
      return static_cast<Type>(type);
    }
    else return OTHER;
  }
}
