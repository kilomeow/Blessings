#include "symbol_utf8.hpp"
#include "symbol_utf8_impl.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdint>

using namespace std;

namespace blessings {
  SymbolUTF8::SymbolUTF8(char c) noexcept {
    if (c&0b10000000) {
      arr_[0]=0b11000000|(c>>6);
      arr_[1]=0b10000000|(c&0b00111111);

      size_=2;
    }
    else {
      arr_[0]=c;

      size_=1;
    }
  }

  SymbolUTF8::SymbolUTF8(char32_t x) {
    if (x&0xff000000) size_=4;
    else if (x&0x00ff0000) size_=3;
    else if (x&0x0000ff00) size_=2;
    else size_=1;

    Converter conv;
    conv.ch=x;

    switch(size_) {
    case 1:
      arr_[0]=conv.arr_[0];
      if (arr_[0]&0b10000000) throw InitError();
      break;
    case 2:
      arr_[0]=conv.arr_[1];
      arr_[1]=conv.arr_[0];
      if ((arr_[0]&0b11100000)^0b11000000) throw InitError();
      if ((arr_[1]&0b11000000)^0b10000000) throw InitError();
      break;
    case 3:
      arr_[0]=conv.arr_[2];
      arr_[1]=conv.arr_[1];
      arr_[2]=conv.arr_[0];
      if ((arr_[0]&0b11110000)^0b11100000) throw InitError();
      if ((arr_[1]&0b11000000)^0b10000000) throw InitError();
      if ((arr_[2]&0b11000000)^0b10000000) throw InitError();
      break;
    case 4:
      arr_[0]=conv.arr_[3];
      arr_[1]=conv.arr_[2];
      arr_[2]=conv.arr_[1];
      arr_[3]=conv.arr_[0];
      if ((arr_[0]&0b11111000)^0b11110000) throw InitError();
      if ((arr_[1]&0b11000000)^0b10000000) throw InitError();
      if ((arr_[2]&0b11000000)^0b10000000) throw InitError();
      if ((arr_[3]&0b11000000)^0b10000000) throw InitError();
    }
  }

  SymbolUTF8::SymbolUTF8(const char* sym) {
    if (sym==nullptr) throw InitError();
    if (*sym=='\0') throw InitError();

    if (!(sym[0]&0b10000000)) size_=1;
    else if (!((sym[0]&0b11100000)^0b11000000)) size_=2;
    else if (!((sym[0]&0b11110000)^0b11100000)) size_=3;
    else if (!((sym[0]&0b11111000)^0b11110000)) size_=4;
    else throw InitError();

    if (strlen(sym)!=static_cast<size_t>(size_)) throw InitError();

    switch(size_) {
    case 4:
      if (((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for (int8_t i=0; i<size_; ++i) arr_[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(const char* sym, int givenSize) {
    if (sym==nullptr) throw InitError();
    if (givenSize==0) throw InitError();

    if (!(sym[0]&0b10000000)) size_=1;
    else if (!((sym[0]&0b11100000)^0b11000000)) size_=2;
    else if (!((sym[0]&0b11110000)^0b11100000)) size_=3;
    else if (!((sym[0]&0b11111000)^0b11110000)) size_=4;
    else throw InitError();

    if (givenSize!=static_cast<int>(size_)) throw InitError();

    switch(size_) {
    case 4:
      if (((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for (int8_t i=0; i<size_; ++i) arr_[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(const std::string& sym) {
    if(sym.size()==0) throw InitError();

    if (!(sym[0]&0b10000000)) size_=1;
    else if (!((sym[0]&0b11100000)^0b11000000)) size_=2;
    else if (!((sym[0]&0b11110000)^0b11100000)) size_=3;
    else if (!((sym[0]&0b11111000)^0b11110000)) size_=4;
    else throw InitError();

    if (sym.size()!=static_cast<size_t>(size_)) throw InitError();

    switch(size_) {
    case 4:
      if (((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for (int8_t i=0; i<size_; ++i) arr_[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(const std::initializer_list<char>& sym) {
    if(sym.size()==0) throw InitError();

    if (!(*sym.begin()&0b10000000)) size_=1;
    else if (!((*sym.begin()&0b11100000)^0b11000000)) size_=2;
    else if (!((*sym.begin()&0b11110000)^0b11100000)) size_=3;
    else if (!((*sym.begin()&0b11111000)^0b11110000)) size_=4;
    else throw InitError();

    if (sym.size()!=static_cast<size_t>(size_)) throw InitError();

    switch(size_) {
    case 4:
      if (((*(sym.begin()+3)&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((*(sym.begin()+2)&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((*(sym.begin()+1)&0b11000000)^0b10000000)) throw InitError();
    }

    auto it=sym.begin();
    for (int8_t i=0; i<size_; ++i, ++it) arr_[i]=*it;
  }

  SymbolUTF8::SymbolUTF8(uint32_t x) {
    if (x<0x7F) size_=1;
    else if (x<0x7FF) size_=2;
    else if (x<0xFFFF) size_=3;
    else if (x<0x1FFFFF) size_=4;
    else throw InitError();

    Converter conv;
    conv.ui=x;

    switch(size_) {
    case 1:
      arr_[0]=conv.arr_[0];
      break;
    case 2:
      arr_[1]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[0]=(conv.arr_[0]&0b00011111)|0b11000000;
      break;
    case 3:
      arr_[2]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[1]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[0]=(conv.arr_[0]&0b00001111)|0b11100000;
      break;
    case 4:
      arr_[3]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[2]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[1]=(conv.arr_[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr_[0]=(conv.arr_[0]&0b00000111)|0b11110000;
    }
  }

  SymbolUTF8::SymbolUTF8(const SymbolUTF8& sym) {
    for (int i=0; i<4; ++i) arr_[i]=sym.arr_[i];
    size_=sym.size_;
  }

  const SymbolUTF8& SymbolUTF8::operator=(const SymbolUTF8& sym) {
    if (*this==sym) return *this;

    for (int i=0; i<4; ++i) arr_[i]=sym.arr_[i];
    size_=sym.size_;
    return (*this);
  }

  char SymbolUTF8::operator()(int i) const {
    if(i<0 || i>3) throw AccessError();

    return arr_[i];
  }

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym) {
    for (int i=0; i<sym.size_; ++i) {
      try {
        stream << sym.arr_[i];
      }
      catch (...) {
        throw SymbolUTF8::IOError();
      }
    }

    return stream;
  }

  std::pair<SymbolUTF8, const char*> SymbolUTF8::getSymbol(const char* str) {
    if(str==nullptr) throw InitError();

    return getSymbol(str, str+strlen(str));
  }

  SymbolUTF8 SymbolUTF8::getSymbol(const char* str,\
  size_t n) {
    if(n==0) throw InitError();
    else if(str==nullptr) throw InitError();

    int size;
    if (!(str[0]&0b10000000)) size=1;
    else if (!((str[0]&0b11100000)^0b11000000)) size=2;
    else if (!((str[0]&0b11110000)^0b11100000)) size=3;
    else size=4;

    if(n<static_cast<size_t>(size)) throw InitError();

    return SymbolUTF8(str, size);
  }

  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym) {
    SymbolUTF8 ret;
    try {
      stream.get(ret.arr_[0]);
    }
    catch (...) {
      throw SymbolUTF8::IOError();
    }

    if (!(ret.arr_[0]&0b10000000)) ret.size_=1;
    else if (!((ret.arr_[0]&0b11100000)^0b11000000)) ret.size_=2;
    else if (!((ret.arr_[0]&0b11110000)^0b11100000)) ret.size_=3;
    else if (!((ret.arr_[0]&0b11111000)^0b11110000)) ret.size_=4;
    else throw SymbolUTF8::IOError();

    for (int8_t i=1; i<ret.size_; ++i) {
      try {
        stream.get(ret.arr_[i]);
      }
      catch (...) {
        throw SymbolUTF8::IOError();
      }
    }

    switch(ret.size_) {
    case 4:
      if (((ret.arr_[3]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 3:
      if (((ret.arr_[2]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 2:
      if (((ret.arr_[1]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    }

    sym=ret;

    return stream;
  }

  std::string SymbolUTF8::toString() const {
    return std::string(arr_, size_);
  }

  bool operator==(const SymbolUTF8& a, const SymbolUTF8& b) {
    int aSize=a.size_;
    int bSize=b.size_;
    if(aSize!=bSize) return false;

    bool ret=true;
    for (int i=0; i<aSize; ++i) {
      if (a.arr_[i]!=b.arr_[i]) {
        ret=false;
        break;
      }
    }

    return ret;
  }

  bool operator!=(const SymbolUTF8& a, const SymbolUTF8& b) {
    int aSize=a.size_;
    int bSize=b.size_;
    if(aSize!=bSize) return true;

    bool ret=false;
    for (int i=0; i<aSize; ++i) {
      if (a.arr_[i]!=b.arr_[i]) {
        ret=true;
        break;
      }
    }

    return ret;
  }

  void SymbolUTF8::writeToFile(FILE* file) const {
    for (int8_t i=0; i<size_; ++i) {
      int temp=fputc(static_cast<int>(arr_[i]), file);
      if (temp==EOF) throw SymbolUTF8::IOError();
    }
  }

  SymbolUTF8 SymbolUTF8::readFromFile(FILE* file) {
    int temp=getc(file);
    if (temp==EOF) throw SymbolUTF8::IOError();

    SymbolUTF8 ret;
    ret.arr_[0]=static_cast<char>(temp);

    if (!(ret.arr_[0]&0b10000000)) ret.size_=1;
    else if (!((ret.arr_[0]&0b11100000)^0b11000000)) ret.size_=2;
    else if (!((ret.arr_[0]&0b11110000)^0b11100000)) ret.size_=3;
    else if (!((ret.arr_[0]&0b11111000)^0b11110000)) ret.size_=4;
    else throw SymbolUTF8::IOError();

    for (int8_t i=1; i<ret.size_; ++i) {
      temp=getc(file);
      if (temp==EOF) throw SymbolUTF8::IOError();

      ret.arr_[i]=static_cast<char>(temp);

      if ((ret.arr_[i]&0b11000000)^0b10000000) throw SymbolUTF8::IOError();
    }

    return ret;
  }

  SymbolUTF8::operator char32_t() const {
    Converter conv;
    conv.ch=0;

    const char* ch=arr_;
    uint8_t size=size_;
    while (size) {
      conv.ch<<=8;
      conv.arr_[0]=*ch;

      --size;
      ++ch;
    }

    return conv.ch;
  }

  uint32_t SymbolUTF8::unicode() const {
    Converter conv;
    conv.ui=0;

    switch(size_) {
    case 1:
      conv.arr_[0]=arr_[0];
      return conv.ui;
    case 2:
      conv.arr_[0]=arr_[0]&0b00011111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[1]&0b00111111;
      return conv.ui;
    case 3:
      conv.arr_[0]=arr_[0]&0b00001111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[1]&0b00111111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[2]&0b00111111;
      return conv.ui;
    case 4:
      conv.arr_[0]=arr_[0]&0b00000111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[1]&0b00111111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[2]&0b00111111;
      conv.ui<<=6;
      conv.arr_[0]|=arr_[3]&0b00111111;
      return conv.ui;
    }
  }
}
