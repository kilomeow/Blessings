#include <iostream>

#include "test_string_utf8.hpp"
#include "string_utf8.hpp"

using namespace std;

namespace blessings {
  void test_StringUTF8() {
    cout << "===================================" << endl;
    cout << "Тестируется StringUTF8..." << endl;

    StringUTF8 str1="Я строка символов UTF-8!"_sUTF8;
    cout << str1 << endl;
    StringUTF8 str2(str1.toString());
    cout << str2 << endl;
    StringUTF8 str3(str1.toCharString());
    cout << str3 << endl;

    cout << endl;

    if(str3==str1) cout << "OK" << endl;
    else cout << "BAD" << endl;
  }
}
