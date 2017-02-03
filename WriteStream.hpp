#pragma once

<<<<<<< 21b2521866acb0504f36eb8b189da7744358d685
namespace Blessings_ns {
  template <class OutputSymbol, class Color>
  class WriteStream {
    virtual write(OutputSymbol, Color)=0;
  };
}
=======
#include "Symbol.hpp"




class WriteStream
{
public:

	WriteStream() {}

	int print(Symbol S)               // Must return 0 if symbol was written and 1 if symbol is terminating.
	{
		if (S==Symbol("\0")) return 1;
		return 0;
	}

	void newLine() {}                 // Printing '\n' symbol

	void clearScreen() {}             // Clearing screen

};
>>>>>>> First commit
