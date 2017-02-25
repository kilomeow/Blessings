#pragma once

#include <string>
#include <iostream>
#include <cstdio>

#include "Symbol.hpp"

namespace blessings {
  class SymbolUTF8 {
    char arr[4]; //char in c++ is always 1 byte
  public:
    class Error;
    class IOError;
    class InitError;
    class AccessError;

    SymbolUTF8() {arr[0]=static_cast<char>(0x0);};
    explicit SymbolUTF8(char c);
    explicit SymbolUTF8(const char* sym);
    explicit SymbolUTF8(int32_t);
    explicit SymbolUTF8(std::string sym);

    SymbolUTF8(const SymbolUTF8&);
    const SymbolUTF8& operator=(const SymbolUTF8&);

    std::string getString() const;

    char& operator[](int pos);
    char operator[](int pos) const;

    int getSize() const;

    uint32_t getUnicode() const;

    operator int32_t();

    bool isSpace() const;

    friend bool operator==(const SymbolUTF8&, const SymbolUTF8&);
    friend bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

    friend std::ostream& operator<<(std::ostream&, const SymbolUTF8&);
    friend std::istream& operator>>(std::istream&, SymbolUTF8&);

    friend SymbolUTF8 readSymbol<SymbolUTF8>(FILE*);
    friend void writeSymbol<SymbolUTF8>(const SymbolUTF8&, FILE*);
  };

  template <>
  SymbolUTF8 readSymbol<SymbolUTF8>(FILE*);
  template <>
  void writeSymbol<SymbolUTF8>(const SymbolUTF8&, FILE*);

  bool operator==(const SymbolUTF8&, const SymbolUTF8&);
  bool operator!=(const SymbolUTF8&, const SymbolUTF8&);

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym);
  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym);

  //Errors
  class SymbolUTF8::Error : public BlessingsError {};
  class SymbolUTF8::IOError : public SymbolUTF8::Error {};
  class SymbolUTF8::InitError : public SymbolUTF8::Error {};
  class SymbolUTF8::AccessError : public SymbolUTF8::Error {};

  //String
  struct SymbolUTF8_traits {
    typedef SymbolUTF8 char_type;
    typedef int32_t int_type;

    static void assign(SymbolUTF8& r, const SymbolUTF8& a) {r=a;};
    static SymbolUTF8* assign(SymbolUTF8* p, size_t count, SymbolUTF8 a);

    static bool eq(SymbolUTF8 a, SymbolUTF8 b) {return a==b;}
    static bool lt(SymbolUTF8 a, SymbolUTF8 b) {return a.getUnicode()<b.getUnicode();}

    static SymbolUTF8* move(SymbolUTF8* dest, const SymbolUTF8* src, size_t count);

    static SymbolUTF8* copy(SymbolUTF8* dest, const SymbolUTF8* src, size_t count);

    static int32_t compare(const SymbolUTF8* s1, const SymbolUTF8* s2, size_t count);

    static size_t length(const SymbolUTF8* s);

    static const SymbolUTF8* find(const SymbolUTF8* p, size_t count, const SymbolUTF8& ch);

    static SymbolUTF8 to_char_type(int32_t c);

    static int32_t to_int_type(SymbolUTF8 c);

    static bool eq_int_type(int32_t c1, int32_t c2) {return c1==c2;};

    static int32_t eof() {return 0b10000000;};

    static int32_t not_eof(int32_t e) {
      if(e!=0b10000000) return e;
      else return 0b11000000;
    }
  };

  typedef std::basic_string<SymbolUTF8, SymbolUTF8_traits> StringUTF8;

  std::ostream& operator<<(std::ostream& stream, const StringUTF8& str);
  std::istream& operator>>(std::istream& stream, StringUTF8& str);
}
