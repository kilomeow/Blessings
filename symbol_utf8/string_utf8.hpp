#include <string>

#include "symbol_utf8.hpp"
#include "../error.hpp"

namespace blessings {
  struct SymbolUTF8Traits {
    typedef char32_t char_type;
    typedef int32_t int_type;

    static void assign(char_type& r, const SymbolUTF8& a) {r=a;};
    static char_type* assign(char_type* p, size_t count, char_type a);

    static bool eq(char_type a, char_type b) {return a==b;}
    static bool lt(char_type a, char_type b) {return SymbolUTF8(a).unicode()<SymbolUTF8(b).unicode();}

    static char_type* move(char_type* dest, const char_type* src, size_t count);

    static char_type* copy(char_type* dest, const char_type* src, size_t count);

    static int32_t compare(const char_type* s1, const char_type* s2, size_t count);

    static size_t length(const char_type* s);

    static const char_type* find(const char_type* p, size_t count, const char_type& ch);

    static char_type to_char_type(int32_t c);

    static int32_t to_int_type(char_type c);

    static bool eq_int_type(int32_t c1, int32_t c2);

    static int32_t eof() {return 0b10000000;};

    static int32_t not_eof(int32_t e) {
      if(e!=0b10000000) return e;
      else return 0b11000000;
    }
  };

  class StringUTF8 : public std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits> {
  public:
    class Error {};
    class NonUTF8StringGiven : public Error {};
    class IOError : public Error {};
    class InputError : public IOError {};
    class OutputError : public IOError {};
    class InitError : public Error {};

    explicit StringUTF8(const allocator_type& alloc=allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(alloc) {};

    StringUTF8(size_t count, SymbolUTF8 sym,\
    const allocator_type& alloc=allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(count, sym, alloc) {};

    StringUTF8(const StringUTF8& other, size_t pos,
    size_t count=std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>::npos,
    const allocator_type& alloc = allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(other, pos, count, alloc) {};

    StringUTF8(const SymbolUTF8* s, size_t count,
    const allocator_type& alloc=allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>((SymbolUTF8Traits::char_type*)s, count, alloc) {};

    StringUTF8(const SymbolUTF8* s, const allocator_type& alloc=allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>((SymbolUTF8Traits::char_type*)s, alloc) {};

    template <class InputIt>
    StringUTF8(InputIt first, InputIt last,
    const allocator_type& alloc=allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(first, last, alloc) {};

    StringUTF8(const StringUTF8& other) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(other) {};

    StringUTF8(const StringUTF8& other, const allocator_type& alloc) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(other, alloc) {};

    StringUTF8(StringUTF8&& other) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(other) {};

    StringUTF8(StringUTF8&& other, const allocator_type& alloc) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(other, alloc) {};

    StringUTF8(std::initializer_list<SymbolUTF8Traits::char_type> init,
    const allocator_type& alloc = allocator_type()) :
    std::basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>(init, alloc) {};


    StringUTF8& operator=(const StringUTF8&);
    StringUTF8& operator=(StringUTF8&&);
    StringUTF8& operator=(const SymbolUTF8*);
    StringUTF8& operator=(SymbolUTF8);
    StringUTF8& operator=(std::initializer_list<SymbolUTF8Traits::char_type>);


    StringUTF8(const char*);
    StringUTF8(const std::string&);

    std::string toString();
    char* toCharString();
  };

  std::ostream& operator<<(std::ostream& stream, const StringUTF8& str);
  std::istream& operator>>(std::istream& stream, StringUTF8& str);

  StringUTF8 operator "" _sUTF8(const char*, size_t);
}
