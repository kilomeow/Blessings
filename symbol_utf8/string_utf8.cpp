#include <iostream>
#include <string>
#include <cstring>
#include <locale>

#include "string_utf8.hpp"
#include "symbol_utf8.hpp"
#include "symbol_utf8_impl.hpp"

using namespace std;

namespace blessings {
  SymbolUTF8Traits::char_type* SymbolUTF8Traits::assign(SymbolUTF8Traits::char_type* p, size_t count, SymbolUTF8Traits::char_type a) {
    for (size_t i=0; i<count; ++i) p[i]=a;
    return p;
  }

  SymbolUTF8Traits::char_type* SymbolUTF8Traits::move(SymbolUTF8Traits::char_type* dest, const SymbolUTF8Traits::char_type* src, size_t count) {
    auto temp=new SymbolUTF8Traits::char_type[count];
    for (size_t i=0; i<count; ++i) temp[i]=src[i];
    for (size_t i=0; i<count; ++i) dest[i]=temp[i];
    delete [] temp;

    return dest;
  }

  SymbolUTF8Traits::char_type* SymbolUTF8Traits::copy(SymbolUTF8Traits::char_type* dest, const SymbolUTF8Traits::char_type* src, size_t count) {
    for (size_t i=0; i<count; ++i) dest[i]=src[i];

    return dest;
  }

  int32_t SymbolUTF8Traits::compare(const SymbolUTF8Traits::char_type* s1, const SymbolUTF8Traits::char_type* s2, size_t count) {
    for (size_t i=0; i<count; ++i) {
      if (SymbolUTF8(s1[i]).unicode()<SymbolUTF8(s2[i]).unicode()) return -1;
      else if (SymbolUTF8(s2[i]).unicode()>SymbolUTF8(s2[i]).unicode()) return 1;
    }

    return 0;
  }

  size_t SymbolUTF8Traits::length(const SymbolUTF8Traits::char_type* s) {
    size_t ret=0;
    while (SymbolUTF8(s[ret])!=SymbolUTF8()) ++ret;
    return ret;
  }

  const SymbolUTF8Traits::char_type* SymbolUTF8Traits::find(const SymbolUTF8Traits::char_type* p, size_t count, const SymbolUTF8Traits::char_type& ch) {
    for (size_t i=0; i<count; ++i) if (SymbolUTF8(p[i])==SymbolUTF8(ch)) return p+i;
    return nullptr;
  }

  SymbolUTF8Traits::char_type SymbolUTF8Traits::to_char_type(int32_t c) {
    SymbolUTF8::Converter conv;
    conv.i=c;
    return SymbolUTF8(conv.ch);
  }

  int32_t SymbolUTF8Traits::to_int_type(SymbolUTF8Traits::char_type c) {
    SymbolUTF8::Converter conv;
    conv.ch=static_cast<char32_t>(c);
    return conv.i;
  }

  bool SymbolUTF8Traits::eq_int_type(int32_t c1, int32_t c2)
  {
    SymbolUTF8::Converter conv1, conv2;
    conv1.i = c1;
    conv2.i = c2;
    return SymbolUTF8(conv1.ch) == SymbolUTF8(conv2.ch);
  }

  std::ostream& operator<<(std::ostream& stream, const StringUTF8& str) {
    try {
      for (auto it=str.begin(); it!=str.end(); ++it) stream << (*it);
    }
    catch (...) {
      throw StringUTF8::OutputError();
    }

    return stream;
  }

  std::istream& operator>>(std::istream& stream, StringUTF8& str) {
    SymbolUTF8 sym;
    str.clear();

    locale loc("");

    try {
      while (stream) {
        stream >> sym;
        if (!isspace(static_cast<wchar_t>(static_cast<char32_t>(sym)), loc)) {
          for (int i=sym.size()-1; i>=0; --i) {
            stream.putback(sym(i));
          }
          break;
        }
      }

      while (stream) {
        stream >> sym;
        if (!isspace(static_cast<wchar_t>(static_cast<char32_t>(sym)), loc)) {
          for (int i=sym.size()-1; i>=0; --i) {
            stream.putback(sym(i));
          }
          break;
        }
        str.push_back(sym);
      }
    }
    catch (std::ios_base::failure&) {
      throw StringUTF8::InputError();
    }
    catch (SymbolUTF8::IOError&) {
      throw StringUTF8::InputError();
    }

    return stream;
  }

  StringUTF8 operator "" _sUTF8(const char* str, size_t n) {
    StringUTF8 ret;

    const char* p=str;
    while (p<str+n) {
      decltype(SymbolUTF8::getSymbol(p, str+n)) temp;
      try {
        temp=SymbolUTF8::getSymbol(p, str+n);
      }
      catch (SymbolUTF8::InitError&) {
        throw StringUTF8::InitError();
      }

      ret.push_back(temp.first);
      p=temp.second;
    }

    if(p>str+n) throw StringUTF8::InitError();

    return ret;
  }

  string StringUTF8::toString() {
    string ret;

    size_t retSize=0;
    for(auto it=begin(); it!=end(); ++it) retSize+=SymbolUTF8(*it).size();

    ret.reserve(retSize);
    for(auto it=begin(); it!=end(); ++it) {
      SymbolUTF8 sym(*it);
      ret.append(sym.data(), sym.size());
    }

    return ret;
  }

  char* StringUTF8::toCharString() {
    char* ret;

    size_t retSize=0;
    for(auto it=begin(); it!=end(); ++it) retSize+=SymbolUTF8(*it).size();

    ret=new char [retSize+1];
    ret[retSize]='\0';

    size_t currPos=0;
    const char* data;
    size_t size;
    for(auto it=begin(); it!=end(); ++it) {
      SymbolUTF8 sym;
      data=sym.data();
      size=sym.size();

      for(size_t i=0; i<size; ++i) ret[currPos+i]=data[i];
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

      basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>::push_back(temp.first);
      p=temp.second;
    }
  }

  StringUTF8::StringUTF8(const string& str) :
  basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>() {
    auto it=str.begin();
    while (it!=str.end()) {
      pair<SymbolUTF8, decltype(it)> temp;
      try {
        temp=SymbolUTF8::getSymbol(it, str.end());
      }
      catch(SymbolUTF8::InitError&) {
        throw NonUTF8StringGiven();
      }

      basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>::push_back(temp.first);
      it=temp.second;
    }
  }

  StringUTF8& StringUTF8::operator=(const StringUTF8& other) {
    if (this==&other) return *this;

    basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>& str=*this;
    str=other;

    return *this;
  };

  StringUTF8& StringUTF8::operator=(StringUTF8&& other) {
    if (this==&other) return *this;

    basic_string<SymbolUTF8Traits::char_type, SymbolUTF8Traits>& str=*this;
    str=other;

    return *this;
  };

  StringUTF8& StringUTF8::operator=(const SymbolUTF8* other) {
    *this=StringUTF8(other);

    return *this;
  };

  StringUTF8& StringUTF8::operator=(SymbolUTF8 sym) {
    *this=StringUTF8(1, sym);

    return *this;
  }

  StringUTF8& StringUTF8::operator=(std::initializer_list<SymbolUTF8Traits::char_type> initList) {
    *this=StringUTF8(initList);

    return *this;
  }
}
