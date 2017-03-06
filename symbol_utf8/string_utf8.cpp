#include <iostream>
#include <string>
#include <cstring>
#include <locale>

#include "string_utf8.hpp"
#include "symbol_utf8.hpp"
#include "symbol_utf8_impl.hpp"

using namespace std;

namespace blessings {
  SymbolUTF8* SymbolUTF8Traits::assign(SymbolUTF8* p, size_t count, SymbolUTF8 a) {
    for (size_t i=0; i<count; ++i) p[i]=a;
    return p;
  }

  SymbolUTF8* SymbolUTF8Traits::move(SymbolUTF8* dest, const SymbolUTF8* src, size_t count) {
    auto temp=new SymbolUTF8[count];
    for (size_t i=0; i<count; ++i) temp[i]=src[i];
    for (size_t i=0; i<count; ++i) dest[i]=temp[i];
    delete [] temp;

    return dest;
  }

  SymbolUTF8* SymbolUTF8Traits::copy(SymbolUTF8* dest, const SymbolUTF8* src, size_t count) {
    for (size_t i=0; i<count; ++i) dest[i]=src[i];

    return dest;
  }

  int32_t SymbolUTF8Traits::compare(const SymbolUTF8* s1, const SymbolUTF8* s2, size_t count) {
    for (size_t i=0; i<count; ++i) {
      if (s1[i].unicode()<s2[i].unicode()) return -1;
      else if (s2[i].unicode()>s2[i].unicode()) return 1;
    }

    return 0;
  }

  size_t SymbolUTF8Traits::length(const SymbolUTF8* s) {
    size_t ret=0;
    while (s[ret]!=SymbolUTF8()) ++ret;
    return ret;
  }

  const SymbolUTF8* SymbolUTF8Traits::find(const SymbolUTF8* p, size_t count, const SymbolUTF8& ch) {
    for (size_t i=0; i<count; ++i) if (p[i]==ch) return p+i;
    return nullptr;
  }

  SymbolUTF8 SymbolUTF8Traits::to_char_type(int32_t c) {
    SymbolUTF8::Converter conv;
    conv.i=c;
    return SymbolUTF8(conv.ch);
  }

  int32_t SymbolUTF8Traits::to_int_type(SymbolUTF8 c) {
    SymbolUTF8::Converter conv;
    conv.ch=static_cast<char32_t>(c);
    return conv.i;
  }

  std::ostream& operator<<(std::ostream& stream, const StringUTF8& str) {
    for (auto it=str.begin(); it!=str.end(); ++it) stream << (*it);
    return stream;
  }

  std::istream& operator>>(std::istream& stream, StringUTF8& str) {
    SymbolUTF8 sym;
    str.clear();

    locale loc("");

    while (stream) {
      stream >> sym;
      if (!isspace(static_cast<char32_t>(sym), loc)) {
        for (int i=sym.size()-1; i>=0; --i) {
          stream.putback(sym(i));
        }
        break;
      }
    }

    while (stream) {
      stream >> sym;
      if (!isspace(static_cast<char32_t>(sym), loc)) {
        for (int i=sym.size()-1; i>=0; --i) {
          stream.putback(sym(i));
        }
        break;
      }
      str.push_back(sym);
    }

    return stream;
  }

  StringUTF8 operator "" _sUTF8(const char* str, size_t n) {
    StringUTF8 ret;

    const char* p=str;
    while (p!=str+n) {
      auto temp=SymbolUTF8::getSymbol(p, str+n);

      ret.push_back(temp.first);
      p=temp.second;
    }

    return ret;
  }

  string StringUTF8::toString() {
    string ret;

    size_t retSize=0;
    for(auto it=begin(); it!=end(); ++it) retSize+=it->size();

    ret.reserve(retSize);
    for(auto it=begin(); it!=end(); ++it) ret.append(it->data(), it->size());

    return ret;
  }

  char* StringUTF8::toCharString() {
    char* ret;

    size_t retSize=0;
    for(auto it=begin(); it!=end(); ++it) retSize+=it->size();

    ret=new char [retSize+1];
    ret[retSize]='\0';

    size_t currPos=0;
    const char* data;
    size_t size;
    for(auto it=begin(); it!=end(); ++it) {
      data=it->data();
      size=it->size();

      for(int i=0; i<size; ++i) ret[currPos+i]=data[i];
      currPos+=size;
    }

    return ret;
  }

  StringUTF8::StringUTF8(const char* str) {
    size_t size=strlen(str);

    const char* p=str;
    while (p!=str+size) {
      pair<SymbolUTF8, const char*> temp;
      try {
        temp=SymbolUTF8::getSymbol(p, str+size);
      }
      catch(SymbolUTF8::InitError&) {
        throw NonUTF8StringGiven();
      }

      basic_string<SymbolUTF8, SymbolUTF8Traits>::push_back(temp.first);
      p=temp.second;
    }
  }

  StringUTF8::StringUTF8(const string& str) :
  basic_string<SymbolUTF8, SymbolUTF8Traits>() {
    size_t size=str.size();

    auto it=str.begin();
    while (it!=str.end()) {
      pair<SymbolUTF8, decltype(it)> temp;
      try {
        temp=SymbolUTF8::getSymbol(it, str.end());
      }
      catch(SymbolUTF8::InitError&) {
        throw NonUTF8StringGiven();
      }

      basic_string<SymbolUTF8, SymbolUTF8Traits>::push_back(temp.first);
      it=temp.second;
    }
  }
}
