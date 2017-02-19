#pragma once

#include <string>
#include <iostream>
#include <cstdio>

#include "Symbol.hpp"

namespace Blessings_ns {
  class SymbolUTF8 : public Symbol{
    char arr[4]; //char in c++ is always 1 byte
  public:
    class Error;
    class IOError;
    class InitError;
    class AccessError;

    SymbolUTF8() {arr[0]=static_cast<char>(0x20);};
    explicit SymbolUTF8(const char* sym);
    explicit SymbolUTF8(std::string sym);

    std::string getString() const;

    char& operator[](int pos);
    char operator[](int pos) const;

    int getSize() const;

    void writeToFile(FILE*) const;

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);

    friend SymbolUTF8 getSym<SymbolUTF8>(FILE*);
  };

  template <>
  SymbolUTF8 getSym<SymbolUTF8>(FILE*);

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);
}
