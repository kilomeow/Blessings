#include <iostream>

#include "Blessings.hpp"
#include "Symbol.hpp"

using namespace std;
using namespace Blessings_ns;

int main() {
  SymbolUTF8 a;

  while(cin) {
    cin >> a;
    cout << a.getSize() << ' ' << a << endl;
  }

  return 0;
}
