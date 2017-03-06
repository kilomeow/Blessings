#include "symbol.hpp"
#include "../error.hpp"

namespace blessings {
  const ColorANSI ColorANSI::defaultColor=ColorANSI(NONE);

  const PropertyANSI PropertyANSI::defaultProperty=PropertyANSI();

  bool operator==(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics==b.italics && a.bold==b.bold && a.color==b.color && \
      a.backgroundColor==b.backgroundColor;
  }

  bool operator!=(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics!=b.italics || a.bold!=b.bold || a.color!=b.color || \
      a.backgroundColor!=b.backgroundColor;
  }
}
