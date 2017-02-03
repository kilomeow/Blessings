#pragma once

#include "Terminal.hpp"




class TerminalFake : public Terminal
{
public:

    int getWidth()
    {
    	return 20;
    }
    int getHeight()
    {
    	return 16;
    }

};

