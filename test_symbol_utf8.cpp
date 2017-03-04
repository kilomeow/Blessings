#include <iostream>

#include "symbol/symbol_utf8.hpp"
#include "test_symbol_utf8.hpp"

using namespace std;

namespace blessings {
  static const SymbolUTF8 testSym1('b');
  static const SymbolUTF8 testSym2("ф");

  static bool test_constructor() {
    SymbolUTF8 sym1('a');
    cout << "const char* constructor: " << sym1 << endl;
    SymbolUTF8 sym2(sym1.data(), 1);
    cout << "const char*, size_t constructor: " << sym2 << endl;
    SymbolUTF8 sym3(static_cast<char32_t>(sym2));
    cout << "char32_t constructor: " << sym3 << endl;
    SymbolUTF8 sym4(sym3.unicode());
    cout << "unicode constructor: " << sym4 << endl;
    SymbolUTF8 sym5(sym4.toString());
    cout << "string constructor: " << sym5 << endl;
    SymbolUTF8 sym6({sym5(0)});
    cout << "initializer_list constructor: " << sym6 << endl;

    if (sym6!=sym1 || sym6.toString()!="a") return false;

    cout << endl;

    sym1=SymbolUTF8("ф");
    cout << "const char* constructor: " << sym1 << endl;
    sym2=SymbolUTF8(sym1.data(), 2);
    cout << "const char*, size_t constructor: " << sym2 << endl;
    sym3=SymbolUTF8(static_cast<char32_t>(sym2));
    cout << "char32_t constructor: " << sym3 << endl;
    sym4=SymbolUTF8(sym3.unicode());
    cout << "unicode constructor: " << sym4 << endl;
    sym5=SymbolUTF8(sym4.toString());
    cout << "string constructor: " << sym5 << endl;
    sym6=SymbolUTF8({sym5(0), sym5(1)});
    cout << "initializer_list constructor: " << sym6 << endl;

    if (sym6!=sym1 || sym6.toString()!="ф") return false;
    return true;
  }

  static bool test_accessOperator() {
    SymbolUTF8 sym1("字");
    SymbolUTF8 sym2=SymbolUTF8(sym1.unicode());

    return sym1==sym2;
  }

  static bool test_toString_data() {
    SymbolUTF8 sym1("字");
    SymbolUTF8 sym2=SymbolUTF8(sym1.toString());
    SymbolUTF8 sym3=SymbolUTF8(sym2.data(), sym2.size());

    return sym1==sym3;
  }

  static bool test_unicode_char32_tConv() {
    SymbolUTF8 sym1("字");
    SymbolUTF8 sym2=SymbolUTF8(sym1.unicode());
    SymbolUTF8 sym3=SymbolUTF8(static_cast<char32_t>(sym2));

    return sym1==sym3;
  }

  void test_SymbolUTF8() {
    cout << "========================================" << endl;
    cout << "Testing SymbolUTF8 class..." << endl;
    cout << endl;

    cout << "Testing constructors and operator=..." << endl;
    if(test_constructor()) cout << "OK" << endl;
    else {
      cerr << "BAD" << endl;
      return;
    }

    cout << endl << endl;

    cout << "Testing operator()..." << endl;
    if(test_accessOperator()) cout << "OK" << endl;
    else {
      cerr << "BAD" << endl;
      return;
    }

    cout << endl << endl;

    cout << "Testing teString() and data()..." << endl;
    if(test_toString_data()) cout << "OK" << endl;
    else {
      cerr << "BAD" << endl;
      return;
    }

    cout << endl << endl;

    cout << "Testing unicode() and char32_t convertion..." << endl;
    if(test_unicode_char32_tConv()) cout << "OK" << endl;
    else {
      cerr << "BAD" << endl;
      return;
    }

    cout << endl << "SymbolUTF8 class tested, no errors" << endl;
  }
}
