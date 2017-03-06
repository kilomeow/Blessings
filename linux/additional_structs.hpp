#pragma once

namespace blessings {
  template <typename Symbol>
  struct CheckedSymbol {
    bool notEmpty;
    Symbol sym;
  }
}
