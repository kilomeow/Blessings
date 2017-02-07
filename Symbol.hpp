#pragma once

//Warning: symbol and property shold have const static std::string info field!

#include <string>
#include <iostream>

namespace Blessings_ns {
  class SymbolUTF8 {
    char arr[4]; //char in c++ is always 1 byte
  public:
    class Error;

    explicit SymbolUTF8(char a=0);
    explicit SymbolUTF8(const char* sym);
    explicit SymbolUTF8(std::string sym);

    char& operator[](int pos);
    char operator[](int pos) const;

    int getSize() const;

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);
  };

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);
}
