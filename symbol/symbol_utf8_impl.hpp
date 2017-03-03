#include <utility>

#include "symbol_utf8.hpp"

namespace blessings {
  template <typename CharIteratorT>
  std::pair<SymbolUTF8, CharIteratorT> SymbolUTF8::getSymbol(\
  CharIteratorT begin, CharIteratorT end) {
    if(begin==end) throw SymbolUTF8::InitError();

    std::pair<SymbolUTF8, CharIteratorT> ret;
    ret.first.arr[0]=*begin;

    int size;
    if (!(ret.first.arr[0]&0b10000000)) size=1;
    else if (!((ret.first.arr[0]&0b11100000)^0b11000000)) size=2;
    else if (!((ret.first.arr[0]&0b11110000)^0b11100000)) size=3;
    else if (!((ret.first.arr[0]&0b11111000)^0b11110000)) size=4;
    else throw SymbolUTF8::InitError();

    ++begin;
    ret.second=begin;

    for (int i=1; i<size; ++i, ++ret.second) {
      if(begin==end) throw SymbolUTF8::InitError();

      ret.first.arr[i]=*begin;

      if ((ret.first.arr[i]&0b11000000)^0b10000000) throw SymbolUTF8::InitError();
    }

    return ret;
  }
}
