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
      arr[0]=0b11000000|(c>>6);
      arr[1]=0b10000000|(c&0b00111111);
    }
    else arr[0]=c;
  }

  SymbolUTF8::SymbolUTF8(char32_t x) {
    int size;
    if (x&0xff000000) size=4;
    else if (x&0x00ff0000) size=3;
    else if (x&0x0000ff00) size=2;
    else size=1;

    Converter conv;
    conv.ch=x;

    switch(size) {
    case 1:
      arr[0]=conv.arr[0];
      if (arr[0]&0b10000000) throw InitError();
      break;
    case 2:
      arr[0]=conv.arr[1];
      arr[1]=conv.arr[0];
      if ((arr[0]&0b11100000)^0b11000000) throw InitError();
      if ((arr[1]&0b11000000)^0b10000000) throw InitError();
      break;
    case 3:
      arr[0]=conv.arr[2];
      arr[1]=conv.arr[1];
      arr[2]=conv.arr[0];
      if ((arr[0]&0b11110000)^0b11100000) throw InitError();
      if ((arr[1]&0b11000000)^0b10000000) throw InitError();
      if ((arr[2]&0b11000000)^0b10000000) throw InitError();
      break;
    case 4:
      arr[0]=conv.arr[3];
      arr[1]=conv.arr[2];
      arr[2]=conv.arr[1];
      arr[3]=conv.arr[0];
      if ((arr[0]&0b11111000)^0b11110000) throw InitError();
      if ((arr[1]&0b11000000)^0b10000000) throw InitError();
      if ((arr[2]&0b11000000)^0b10000000) throw InitError();
      if ((arr[3]&0b11000000)^0b10000000) throw InitError();
    }
  }

  SymbolUTF8::SymbolUTF8(const char* sym) {
    if (sym==nullptr) throw InitError();

    int size;
    if (!(sym[0]&0b10000000)) size=1;
    else if (!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if (!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if (!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw InitError();

    if (strlen(sym)!=static_cast<size_t>(size)) throw InitError();

    switch(size) {
    case 4:
      if (((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for (int i=0; i<size; ++i) arr[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(std::string sym) {
    int size;
    if (!(sym[0]&0b10000000)) size=1;
    else if (!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if (!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if (!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw InitError();

    if (sym.size()!=static_cast<size_t>(size)) throw InitError();

    switch(size) {
    case 4:
      if (((sym[3]&0b11000000)^0b10000000)) throw InitError();
    case 3:
      if (((sym[2]&0b11000000)^0b10000000)) throw InitError();
    case 2:
      if (((sym[1]&0b11000000)^0b10000000)) throw InitError();
    }

    for (uint8_t i=0; i<size; ++i) arr[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(uint32_t x) {
    int size;
    if (x<0x7F) size=1;
    else if (x<0x7FF) size=2;
    else if (x<0xFFFF) size=3;
    else if (x<0x1FFFFF) size=4;
    else throw InitError();

    Converter conv;
    conv.ui=x;

    switch(size) {
    case 1:
      arr[0]=conv.arr[0];
      break;
    case 2:
      arr[1]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[0]=(conv.arr[0]&0b00011111)|0b11000000;
      break;
    case 3:
      arr[2]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[1]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[0]=(conv.arr[0]&0b00001111)|0b11100000;
      break;
    case 4:
      arr[3]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[2]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[1]=(conv.arr[0]&0b00111111)|0b10000000;
      conv.ui>>=6;
      arr[0]=(conv.arr[0]&0b00000111)|0b11110000;
    }
  }

  SymbolUTF8::SymbolUTF8(const SymbolUTF8& sym) {
    for (int i=0; i<4; ++i) arr[i]=sym.arr[i];
  }

  const SymbolUTF8& SymbolUTF8::operator=(const SymbolUTF8& sym) {
    if (*this==sym) return *this;

    for (int i=0; i<4; ++i) arr[i]=sym.arr[i];
    return (*this);
  }

  char SymbolUTF8::operator()(int i) const {
    if(i<0 || i>3) throw AccessError();

    return arr[i];
  }

  int SymbolUTF8::getSize() const {
    if (!(arr[0]&0b10000000)) return 1;
    else if (!((arr[0]&0b11100000)^0b11000000)) return 2;
    else if (!((arr[0]&0b11110000)^0b11100000)) return 3;
    else return 4;
  }

  std::ostream& operator<<(std::ostream& stream, const SymbolUTF8& sym) {
    int size=sym.getSize();

    for (int i=0; i<size; ++i) {
      try {
        stream << sym.arr[i];
      }
      catch (...) {
        throw SymbolUTF8::IOError();
      }
    }

    return stream;
  }

  std::pair<SymbolUTF8, const char*> SymbolUTF8::getSymbol(const char* str) {
    return getSymbol(str, str+strlen(str));
  }

  std::pair<SymbolUTF8, const char*> SymbolUTF8::getSymbol(const char* str,\
  size_t n) {
    return getSymbol(str, str+n);
  }

  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym) {
    SymbolUTF8 ret; //UTF-8 space symbol, 1 byte
    try {
      stream.get(ret.arr[0]);
    }
    catch (...) {
      throw SymbolUTF8::IOError();
    }

    int size;
    if (!(ret.arr[0]&0b10000000)) size=1;
    else if (!((ret.arr[0]&0b11100000)^0b11000000)) size=2;
    else if (!((ret.arr[0]&0b11110000)^0b11100000)) size=3;
    else if (!((ret.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::IOError();

    for (int i=1; i<size; ++i) {
      try {
        stream.get(ret.arr[i]);
      }
      catch (...) {
        throw SymbolUTF8::IOError();
      }
    }

    switch(size) {
    case 4:
      if (((ret.arr[3]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 3:
      if (((ret.arr[2]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    case 2:
      if (((ret.arr[1]&0b11000000)^0b10000000)) throw SymbolUTF8::IOError();
    }

    sym=ret;

    return stream;
  }

  std::string SymbolUTF8::getString() const {
    return std::string(arr, getSize());
  }

  bool operator==(const SymbolUTF8& a, const SymbolUTF8& b) {
    int aSize=a.getSize();
    int bSize=b.getSize();
    if(aSize!=bSize) return false;

    bool ret=true;
    for (int i=0; i<aSize; ++i) {
      if (a.arr[i]!=b.arr[i]) {
        ret=false;
        break;
      }
    }

    return ret;
  }

  bool operator!=(const SymbolUTF8& a, const SymbolUTF8& b) {
    int aSize=a.getSize();
    int bSize=b.getSize();
    if(aSize!=bSize) return true;

    bool ret=false;
    for (int i=0; i<aSize; ++i) {
      if (a.arr[i]!=b.arr[i]) {
        ret=true;
        break;
      }
    }

    return ret;
  }

  void SymbolUTF8::writeToFile(FILE* file) {
    int size=getSize();
    for (int i=0; i<size; ++i) {
      int temp=fputc(static_cast<int>(arr[i]), file);
      if (temp==EOF) throw SymbolUTF8::IOError();
    }
  }

  SymbolUTF8 SymbolUTF8::readFromFile(FILE* file) {
    int temp=getc(file);
    if (temp==EOF) throw SymbolUTF8::IOError();

    SymbolUTF8 ret; //UTF-8 space symbol, 1 byte
    ret.arr[0]=static_cast<char>(temp);

    int size;
    if (!(ret.arr[0]&0b10000000)) size=1;
    else if (!((ret.arr[0]&0b11100000)^0b11000000)) size=2;
    else if (!((ret.arr[0]&0b11110000)^0b11100000)) size=3;
    else if (!((ret.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::IOError();

    for (int i=1; i<size; ++i) {
      temp=getc(file);
      if (temp==EOF) throw SymbolUTF8::IOError();

      ret.arr[i]=static_cast<char>(temp);

      if ((ret.arr[i]&0b11000000)^0b10000000) throw SymbolUTF8::IOError();
    }

    return ret;
  }

  SymbolUTF8::operator char32_t() {
    int size=getSize();

    Converter conv;
    conv.ch=0;

    char* ch=arr;
    while (size) {
      conv.ch<<=8;
      conv.arr[0]=*ch;

      --size;
      ++ch;
    }

    return conv.ch;
  }

  uint32_t SymbolUTF8::getUnicode() const {
    int size=getSize();

    Converter conv;
    conv.ui=0;

    switch(size) {
    case 1:
      conv.arr[0]=arr[0];
      return conv.ui;
    case 2:
      conv.arr[0]=arr[0]&0b00011111;
      conv.ui<<=6;
      conv.arr[0]|=arr[1]&0b00111111;
      return conv.ui;
    case 3:
      conv.arr[0]=arr[0]&0b00001111;
      conv.ui<<=6;
      conv.arr[0]|=arr[1]&0b00111111;
      conv.ui<<=6;
      conv.arr[0]|=arr[2]&0b00111111;
      return conv.ui;
    case 4:
      conv.arr[0]=arr[0]&0b00000111;
      conv.ui<<=6;
      conv.arr[0]|=arr[1]&0b00111111;
      conv.ui<<=6;
      conv.arr[0]|=arr[2]&0b00111111;
      conv.ui<<=6;
      conv.arr[0]|=arr[3]&0b00111111;
      return conv.ui;
    }
  }

  bool SymbolUTF8::isSpace() const {
    if (getSize()==1) {
      if (arr[0]==0x20 || arr[0]==0x0c || arr[0]==0x0a || arr[0]==0x0d || arr[0]==0x09\
        || arr[0]==0x0b) return true;
    }

    return false;
  }
}
