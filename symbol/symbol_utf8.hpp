#pragma once

#include <string>
#include <iostream>
#include <cstdio>
#include <utility>

#include "../error.hpp"

namespace blessings {
  class SymbolUTF8 { //Only for little-endian systems!
    char arr_[4]; //char in c++ is always 1 byte
    int8_t size_;

    operator uint32_t() const;
  public:
    class Error;
    class IOError;
    class InitError;
    class AccessError;

    union Converter {
      char arr_[4];
      char32_t ch;
      int32_t i;
      uint32_t ui;
    };

    SymbolUTF8() noexcept {arr_[0]=static_cast<char>(0x0);};
    SymbolUTF8(char c) noexcept;
    explicit SymbolUTF8(const char* sym);
    explicit SymbolUTF8(const char* sym, int size);
    explicit SymbolUTF8(char32_t); //from char32_t utf-8 symbol
    explicit SymbolUTF8(uint32_t); //from Unicode number
    explicit SymbolUTF8(const std::string& sym);
    explicit SymbolUTF8(const std::initializer_list<char>&);

    SymbolUTF8(const SymbolUTF8&);
    const SymbolUTF8& operator=(const SymbolUTF8&);

    char operator()(int i) const;

    std::string toString() const;
    const char* data() const {return arr_;};

    int size() const {return size_;};

    uint32_t unicode() const;

    operator char32_t();

    friend bool operator==(const SymbolUTF8&, const SymbolUTF8&);
    friend bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);

    static SymbolUTF8 readFromFile(FILE*);
    void writeToFile(FILE*);

    static std::pair<SymbolUTF8, const char*> getSymbol(const char* str);
    static std::pair<SymbolUTF8, const char*> getSymbol(const char* str,\
    size_t n);
    template <typename CharIteratorT>
    static std::pair<SymbolUTF8, CharIteratorT> getSymbol(CharIteratorT begin,
    CharIteratorT end);
  };

  bool operator==(const SymbolUTF8&, const SymbolUTF8&);
  bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);

  //Errors
  class SymbolUTF8::Error : public BlessingsError {};
  class SymbolUTF8::IOError : public SymbolUTF8::Error {};
  class SymbolUTF8::InitError : public SymbolUTF8::Error {};
  class SymbolUTF8::AccessError : public SymbolUTF8::Error {};
}
