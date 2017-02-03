#pragma once

#include <stdio.h>

#include "Symbol.hpp"
#include "WriteStream.hpp"




class WriteStdIO : public WriteStream
{
public:

	int print(Symbol S)
	{
		if (S==Symbol("\0")) return 1;
		printf("%s", S.str().c_str());
		return 0;
	}

	void newLine()
	{
		printf("\n");
	}

	void clearScreen()
	{
        printf("\n\n\n\n\n\n\n\n");
	}

};
