#pragma once

// Test for a little-endian machine
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Machines with non-little endian orders for SymbolUTF8 is not supported"
#endif

#include "../error.hpp"

#include <string>
#include <iostream>
#include <cstdio>
#include <utility>

namespace blessings {
  class SymbolUTF8 { //Only for little-endian systems!
    char arr_[4]; //char in c++ is always 1 byte
    int8_t size_;

    operator uint32_t() const;
  public:
    class Error : public SymbolError {};
    class IOError : public Error {};
    class ReadError : public IOError {};
    class WriteError : public IOError {};
    class BadEncodingStreamGiven : public Error {};
    class EndOfFile : public IOError {};
    class InitError : public Error {};
    class AccessError : public Error {};

    union Converter {
      char arr_[4];
      char32_t ch;
      int32_t i;
      uint32_t ui;
    };

    SymbolUTF8() noexcept {arr_[0]=static_cast<char>(0x0);};
    SymbolUTF8(char c) noexcept;
    SymbolUTF8(const char* sym);
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

    operator char32_t() const;

    friend bool operator==(const SymbolUTF8&, const SymbolUTF8&);
    friend bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);

    static SymbolUTF8 readFromFile(FILE*);
    void writeToFile(FILE*) const;

    static std::pair<SymbolUTF8, const char*> getSymbol(const char* str);
    SymbolUTF8 getSymbol(const char* str, size_t n);
    template <typename CharIteratorT>
    static std::pair<SymbolUTF8, CharIteratorT> getSymbol(CharIteratorT begin,
    CharIteratorT end);

    static const SymbolUTF8 space;
  };

  bool operator==(const SymbolUTF8&, const SymbolUTF8&);
  bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

  bool operator<=(const SymbolUTF8&, const SymbolUTF8&);
  bool operator<(const SymbolUTF8&, const SymbolUTF8&);
  bool operator>=(const SymbolUTF8&, const SymbolUTF8&);
  bool operator>(const SymbolUTF8&, const SymbolUTF8&);

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);
}
