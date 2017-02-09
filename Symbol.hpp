#pragma once

//Warning: symbol and property shold have const static std::string info field!

#include <string>
#include <iostream>
#include <cstdio>

namespace Blessings_ns {
  class Symbol {
  public:
    virtual std::string getString()=0;
  };

  template <class SymbolType>
  SymbolType getSym(FILE*);

  class SymbolUTF8 : public Symbol{
    char arr[4]; //char in c++ is always 1 byte
  public:
    class Error;

    explicit SymbolUTF8(char a=0);
    explicit SymbolUTF8(const char* sym);
    explicit SymbolUTF8(std::string sym);

    std::string getString();

    char& operator[](int pos);
    char operator[](int pos) const;

    int getSize() const;

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);

    friend SymbolUTF8 getSym<SymbolUTF8>(FILE*);
  };

  template <>
  SymbolUTF8 getSym<SymbolUTF8>(FILE*);

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);
}
