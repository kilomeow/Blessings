#include "property.hpp"

namespace blessings {
  const ColorANSI ColorANSI::defaultColor=ColorANSI(NONE);

  const PropertyANSI PropertyANSI::empty=PropertyANSI(ColorANSI::NONE,
    ColorANSI::NONE, false, false);

  bool operator==(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics==b.italics && a.bold==b.bold && a.color==b.color && \
      a.backgroundColor==b.backgroundColor;
  }

  bool operator!=(const PropertyANSI& a, const PropertyANSI& b) {
    return a.italics!=b.italics || a.bold!=b.bold || a.color!=b.color || \
      a.backgroundColor!=b.backgroundColor;
  }
}
