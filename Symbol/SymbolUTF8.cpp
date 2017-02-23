#include "Symbol.hpp"
#include "SymbolUTF8.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdint>

namespace blessings {
  SymbolUTF8::SymbolUTF8(char c) {
    if(c&0b10000000) throw InitError();
    else arr[0]=c;
  }

  SymbolUTF8::SymbolUTF8(const char* sym) {
    if(sym==nullptr) throw InitError();

    int size;
    if(!(sym[0]&0b10000000)) size=1;
    else if(!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if(!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if(!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw InitError();

    if(strlen(sym)!=size) throw InitError();

    switch(size) {
    case 4:
      if(((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if(((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if(((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for(int i=0; i<size; ++i) arr[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(int32_t x) {
    int size;
    if(x&0xff000000) size=4;
    else if(x&0x00ff0000) size=3;
    else if(x&0x0000ff00) size=2;
    else size=1;

    switch(size) {
    case 1:
      arr[0]=static_cast<char>(x);
      if(arr[0]&0b10000000) throw InitError();
    case 2:
      arr[0]=static_cast<char>(x>>8);
      arr[1]=static_cast<char>(x&0x000000ff);
      if((arr[0]&0b11100000)^0b11000000) throw InitError();
      if((arr[1]&0b11000000)^0b10000000) throw InitError();
    case 3:
      arr[0]=static_cast<char>(x>>16);
      arr[1]=static_cast<char>((x>>8)&0x000000ff);
      arr[2]=static_cast<char>(x&0x000000ff);
      if((arr[0]&0b11110000)^0b11100000) throw InitError();
      if((arr[1]&0b11000000)^0b10000000) throw InitError();
      if((arr[2]&0b11000000)^0b10000000) throw InitError();
    case 4:
      arr[0]=static_cast<char>(x>>24);
      arr[1]=static_cast<char>((x>>16)&0x000000ff);
      arr[2]=static_cast<char>((x>>8)&0x000000ff);
      arr[3]=static_cast<char>(x&0x000000ff);
      if((arr[0]&0b11111000)^0b11110000) throw InitError();
      if((arr[1]&0b11000000)^0b10000000) throw InitError();
      if((arr[2]&0b11000000)^0b10000000) throw InitError();
      if((arr[3]&0b11000000)^0b10000000) throw InitError();
    }
  }

  SymbolUTF8::SymbolUTF8(std::string sym) {
    int size;
    if(!(sym[0]&0b10000000)) size=1;
    else if(!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if(!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if(!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw InitError();

    if(sym.size()!=size) throw InitError();

    switch(size) {
    case 4:
      if(((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if(((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if(((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for(uint8_t i=0; i<size; ++i) arr[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(const SymbolUTF8& sym) {
    for(int i=0; i<4; ++i) arr[i]=sym.arr[i];
  }

  const SymbolUTF8& SymbolUTF8::operator=(const SymbolUTF8& sym) {
    if(*this==sym) return *this;

    for(int i=0; i<4; ++i) arr[i]=sym.arr[i];
    return (*this);
  }

  char& SymbolUTF8::operator[](int pos) {
    if(pos>=4 || pos<0) throw AccessError();

    return arr[pos];
  }

  char SymbolUTF8::operator[](int pos) const {
    if(pos>=4 || pos<0) throw AccessError();

    return arr[pos];
  }

  int SymbolUTF8::getSize() const {
    if(!(arr[0]&0b10000000)) return 1;
    else if(!((arr[0]&0b11100000)^0b11000000)) return 2;
    else if(!((arr[0]&0b11110000)^0b11100000)) return 3;
    else return 4;
  }

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym) {
    int size;
    if(!(sym.arr[0]&0b10000000)) size=1;
    else if(!((sym.arr[0]&0b11100000)^0b11000000)) size=2;
    else if(!((sym.arr[0]&0b11110000)^0b11100000)) size=3;
    else if(!((sym.arr[0]&0b11111000)^0b11110000)) size=4;

    for(int i=0; i<size; ++i) {
      try {
        stream << sym.arr[i];
      }
      catch(...) {
        throw SymbolUTF8::IOError();
      }
    }

    return stream;
  }

  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym) {
    SymbolUTF8 ret; //UTF-8 space symbol, 1 byte
    try {
      stream.get(ret.arr[0]);
    }
    catch(...) {
      throw SymbolUTF8::IOError();
    }

    int size;
    if(!(ret.arr[0]&0b10000000)) size=1;
    else if(!((ret.arr[0]&0b11100000)^0b11000000)) size=2;
    else if(!((ret.arr[0]&0b11110000)^0b11100000)) size=3;
    else if(!((ret.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::IOError();

    for(int i=1; i<size; ++i) {
      try {
        stream.get(ret.arr[i]);
      }
      catch(...) {
        throw SymbolUTF8::IOError();
      }
    }

    switch(size) {
    case 4:
      if(((ret.arr[3]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 3:
      if(((ret.arr[2]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 2:
      if(((ret.arr[1]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    }

    sym=ret;

    return stream;
  }

  std::string SymbolUTF8::getString() const {
    return std::string(arr, getSize());
  }

  bool operator==(const SymbolUTF8& a, const SymbolUTF8& b) {
    bool ret=true;
    for(int i=0; i<4; ++i) {
      if(a.arr[i]!=b.arr[i]) {
        ret=false;
        break;
      }
    }

    return ret;
  }

  bool operator!=(const SymbolUTF8& a, const SymbolUTF8& b) {
    bool ret=false;
    for(int i=0; i<4; ++i) {
      if(a.arr[i]!=b.arr[i]) {
        ret=true;
        break;
      }
    }

    return ret;
  }

  template <>
  void writeSymbol<SymbolUTF8>(const SymbolUTF8& sym, FILE* file) {
    int size=sym.getSize();
    for(int i=0; i<size; ++i) {
      int temp=fputc(static_cast<int>(sym.arr[i]), file);
      if(temp==EOF) throw SymbolUTF8::IOError();
    }
  }

  template <>
  SymbolUTF8 getSymbol<SymbolUTF8>(FILE* file) {
    int temp=getc(file);
    if(temp==EOF) throw SymbolUTF8::IOError();

    SymbolUTF8 ret; //UTF-8 space symbol, 1 byte
    ret.arr[0]=static_cast<char>(temp);

    int size;
    if(!(ret.arr[0]&0b10000000)) size=1;
    else if(!((ret.arr[0]&0b11100000)^0b11000000)) size=2;
    else if(!((ret.arr[0]&0b11110000)^0b11100000)) size=3;
    else if(!((ret.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::IOError();

    for(int i=1; i<size; ++i) {
      temp=getc(file);
      if(temp==EOF) throw SymbolUTF8::IOError();

      ret.arr[i]=static_cast<char>(temp);

      if((ret.arr[i]&0b11000000)^0b10000000) throw SymbolUTF8::IOError();
    }

    return ret;
  }

  SymbolUTF8::operator int32_t() {
    int size=getSize();

    int32_t ret=0;
    char* ch=arr;
    while(size) {
      ret<<=8;
      ret+=*ch;

      --size;
      ++ch;
    }
  }

  uint32_t SymbolUTF8::getUnicode() const {
    int size=getSize();

    uint32_t ret=0;
    switch(size) {
    case 1:
      return static_cast<uint32_t>(arr[0]);
    case 2:
      ret=static_cast<uint32_t>(arr[0]&0b00011111);
      ret<<=5;
      ret+=static_cast<uint32_t>(arr[1]&0b00111111);
      return ret;
    case 3:
      ret=static_cast<uint32_t>(arr[0]&0b00001111);
      ret<<=4;
      ret+=static_cast<uint32_t>(arr[1]&0b00111111);
      ret<<=6;
      ret+=static_cast<uint32_t>(arr[2]&0b00111111);
      return ret;
    case 4:
      ret=static_cast<uint32_t>(arr[0]&0b00000111);
      ret<<=5;
      ret+=static_cast<uint32_t>(arr[1]&0b00111111);
      ret<<=6;
      ret+=static_cast<uint32_t>(arr[2]&0b00111111);
      ret<<=6;
      ret+=static_cast<uint32_t>(arr[3]&0b00111111);
      return ret;
    }
  }

  SymbolUTF8* SymbolUTF8_traits::assign(SymbolUTF8* p, size_t count, SymbolUTF8 a) {
    for(size_t i=0; i<count; ++i) p[i]=a;
  }

  SymbolUTF8* SymbolUTF8_traits::move(SymbolUTF8* dest, const SymbolUTF8* src, size_t count) {
    auto temp=new SymbolUTF8[count];
    for(size_t i=0; i<count; ++i) temp[i]=src[i];
    for(size_t i=0; i<count; ++i) dest[i]=temp[i];
    delete [] temp;
  }

  SymbolUTF8* SymbolUTF8_traits::copy(SymbolUTF8* dest, const SymbolUTF8* src, size_t count) {
    for(size_t i=0; i<count; ++i) dest[i]=src[i];
  }

  int32_t SymbolUTF8_traits::compare(const SymbolUTF8* s1, const SymbolUTF8* s2, size_t count) {
    for(size_t i=0; i<count; ++i) {
      if(s1[i].getUnicode()<s2[i].getUnicode()) return -1;
      else if(s2[i].getUnicode()>s2[i].getUnicode()) return 1;
    }

    return 0;
  }

  size_t SymbolUTF8_traits::length(const SymbolUTF8* s) {
    size_t ret=0;
    while(s[ret]!=SymbolUTF8()) ++ret;
    return ret;
  }

  const SymbolUTF8* SymbolUTF8_traits::find(const SymbolUTF8* p, size_t count, const SymbolUTF8& ch) {
    for(size_t i=0; i<count; ++i) if(p[i]==ch) return p+i;
    return nullptr;
  }

  SymbolUTF8 SymbolUTF8_traits::to_char_type(int32_t c) {
    return SymbolUTF8(c);
  }

  int32_t SymbolUTF8_traits::to_int_type(SymbolUTF8 c) {
    return static_cast<int32_t>(c);
  }
}
