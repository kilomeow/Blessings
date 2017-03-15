#pragma once

#include <string>

namespace blessings {
  class BlessingsError {
  public:
    std::string msg;

    void init(const std::string& message) {
      msg=message;
    }
  };

  class SymbolOrStringError : public BlessingsError {};

  class SymbolError : public SymbolOrStringError {};
  class StringError : public SymbolOrStringError {};
}
