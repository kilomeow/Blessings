#include <iostream>

#include "Blessings.hpp"
#include "SymbolUTF8.hpp"

using namespace std;
using namespace Blessings_ns;

int main() {
  auto x=getSym<SymbolUTF8>(stdin);
  cout << x << ' ' << x.getSize() << endl;

  return 0;
}
