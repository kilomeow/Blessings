#include "Symbol.hpp"
#include "Error.hpp"

#include <string>
#include <iostream>
#include <cstring>

namespace Blessings_ns {
  SymbolUTF8::SymbolUTF8(char a) {
    if(a&0b10000000) throw Error("bad init char");

    arr[0]=a;
  }

  SymbolUTF8::SymbolUTF8(const char* sym) {
    if(sym==nullptr) throw Error("nullptr given as const char* string");

    int size;
    if(!(sym[0]&0b10000000)) size=1;
    else if(!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if(!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if(!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw Error("non-UTF-8 symbol given");

    if(strlen(sym)!=size) throw Error("non-UTF-8 symbol given");

    switch(size) {
    case 4:
      if(((sym[3]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    case 3:
      if(((sym[2]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    case 2:
      if(((sym[1]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    }

    for(uint8_t i=0; i<size; ++i) arr[i]=sym[i];
  }

  SymbolUTF8::SymbolUTF8(std::string sym) {
    int size;
    if(!(sym[0]&0b10000000)) size=1;
    else if(!((sym[0]&0b11100000)^0b11000000)) size=2;
    else if(!((sym[0]&0b11110000)^0b11100000)) size=3;
    else if(!((sym[0]&0b11111000)^0b11110000)) size=4;
    else throw Error("non-UTF-8 symbol given");

    if(sym.size()!=size) throw Error("non-UTF-8 symbol given");

    switch(size) {
    case 4:
      if(((sym[3]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    case 3:
      if(((sym[2]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    case 2:
      if(((sym[1]&0b11000000)^0b10000000)) throw Error("non-UTF-8 symbol given");
    }

    for(uint8_t i=0; i<size; ++i) arr[i]=sym[i];
  }

  char& SymbolUTF8::operator[](int pos) {
    if(pos>=4 || pos<0) throw Error("bad access position");

    return arr[pos];
  }

  char SymbolUTF8::operator[](int pos) const {
    if(pos>=4 || pos<0) throw Error("bad access position");

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
      if(stream) stream << sym.arr[i];
      else throw SymbolUTF8::Error("bad output stream state");
    }

    return stream;
  }

  std::istream& operator>>(std::istream& stream, SymbolUTF8& sym) {
    SymbolUTF8 ret;
    stream.get(ret.arr[0]);

    int size;
    if(!(ret.arr[0]&0b10000000)) size=1;
    else if(!((ret.arr[0]&0b11100000)^0b11000000)) size=2;
    else if(!((ret.arr[0]&0b11110000)^0b11100000)) size=3;
    else if(!((ret.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::Error("attempt to input non-UTF-8 symbol");

    for(int i=1; i<size; ++i) {
      if(stream) stream.get(ret.arr[i]);
      else throw SymbolUTF8::Error("bad input stream state");
    }

    switch(size) {
    case 4:
      if(((ret.arr[3]&0b11000000)^0b10000000)) throw SymbolUTF8::Error("non-UTF-8 symbol in input");
    case 3:
      if(((ret.arr[2]&0b11000000)^0b10000000)) throw SymbolUTF8::Error("non-UTF-8 symbol in input");
    case 2:
      if(((ret.arr[1]&0b11000000)^0b10000000)) throw SymbolUTF8::Error("non-UTF-8 symbol in input");
    }

    sym=ret;

    return stream;
  }
}