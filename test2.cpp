#include <iostream>

#include "symbol/symbol_utf8.hpp"
#include "symbol/string_utf8.hpp"

using namespace std;
using namespace blessings;

int main() {
  auto str="Я строка UTF-8 символов!"_sUTF8;

  cout << str << endl;

  SymbolUTF8 sym;

  cin >> sym;

  cout << SymbolUTF8(static_cast<char32_t>(sym)) << endl;
}
