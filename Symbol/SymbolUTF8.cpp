#include "Symbol.hpp"
#include "SymbolUTF8.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>

namespace blessings {
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

  void SymbolUTF8::writeToFile(FILE* file) const {
    int size=getSize();
    for(int i=0; i<size; ++i) {
      int temp=fputc(static_cast<int>(arr[i]), file);
      if(temp==EOF) throw IOError();
    }
  }

  template <>
  SymbolUTF8 getSym<SymbolUTF8>(FILE* file) {
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
}
