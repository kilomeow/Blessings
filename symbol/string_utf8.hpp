#include "symbol_utf8.hpp"

namespace blessings {
  struct SymbolUTF8Traits {
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

  typedef std::basic_string<SymbolUTF8, SymbolUTF8Traits> StringUTF8;

  std::ostream& operator<<(std::ostream& stream, const StringUTF8& str);
  std::istream& operator>>(std::istream& stream, StringUTF8& str);

  StringUTF8 operator "" _sUTF8(const char*, size_t);
}
