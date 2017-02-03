#pragma once

#include <string>



class Symbol
{
std::string smb;
public:

	Symbol()
	{
		smb = "";
	}

	Symbol(std::string S)
	{
        smb = S;
	}

	Symbol operator+(const Symbol& S)
	{
		Symbol s(smb + S.str());
		return s;
	}

	Symbol lcat(std::string S)
	{
		Symbol s(S + smb);
		return s;
	}

	Symbol rcat(std::string S)
	{
		Symbol s(smb + S);
		return s;
	}

	bool operator==(const Symbol& S)
	{
		if (smb == S.str()) return true;
		return false;
	}

	char car() const
	{
		return smb[0];
	}

	std::string str() const
	{
		return smb;
	}


};




class Color
{
public:

	Color() {}

	bool isCorrect() const
	{
		return true;
	}

	Symbol mapTo(Symbol S)
	{
		return S;
	}

};



class ColorANSI : public Color
{
public:

	int clr;
	int bg;

	ColorANSI(int Clr=0, int Bg=0)
	{
		clr = Clr;
		Bg = bg;
	}

	bool isCorrect() const
	{
		if ((0<=clr<8) && (0<=bg<8)) return true;
		return false;
	}

	Symbol mapTo(Symbol S)
	{
		if (isCorrect())
		{
            //std::string c = std::to_string(30+clr);
            //std::string b = std::to_string(40+bg);
            std::string c("31");
            std::string b("41");

			S = S.lcat("\x1b["+c+";"+b+"m");
			S = S.rcat("\x1b[0m");

            return S;
		}
		return S;
	}

};



const Color EmptyColor();
