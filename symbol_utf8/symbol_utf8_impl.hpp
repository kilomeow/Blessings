#include <utility>

#include "symbol_utf8.hpp"

namespace blessings {
  template <typename CharIteratorT>
  std::pair<SymbolUTF8, CharIteratorT> SymbolUTF8::getSymbol(\
  CharIteratorT begin, CharIteratorT end) {
    if(begin==end) throw SymbolUTF8::InitError();

    std::pair<SymbolUTF8, CharIteratorT> ret;
    ret.first.arr_[0]=*begin;

    if (!(ret.first.arr_[0]&0b10000000)) ret.first.size_=1;
    else if (!((ret.first.arr_[0]&0b11100000)^0b11000000)) ret.first.size_=2;
    else if (!((ret.first.arr_[0]&0b11110000)^0b11100000)) ret.first.size_=3;
    else if (!((ret.first.arr_[0]&0b11111000)^0b11110000)) ret.first.size_=4;
    else throw SymbolUTF8::BadEncodingStreamGiven();

    ++begin;
    ret.second=begin;

    for (int i=1; i<ret.first.size_; ++i, ++ret.second) {
      if(ret.second==end) throw SymbolUTF8::BadEncodingStreamGiven();

      ret.first.arr_[i]=*ret.second;

      if ((ret.first.arr_[i]&0b11000000)^0b10000000) throw SymbolUTF8::BadEncodingStreamGiven();
    }

    return ret;
  }
}
