#pragma once

<<<<<<< 21b2521866acb0504f36eb8b189da7744358d685
namespace Blessings_ns {
  template <class InputSymbol>
  class ReadStream;

  template <class OutputSymbol, class Color>
  class WriteStream;

  template <class OutputSymbol, class Color>
  class Monitor {
  };
}
=======
#include "Symbol.hpp"
#include "Terminal.hpp"
#include "WriteStream.hpp"




// class MonitorError;
// class GridOverflow;
// class GridBoundaryExit;




class MonitorCell
{
public:

	Symbol csymbol;
	Color ccolor;

	MonitorCell()
	{
		Symbol csymbol();
		Color ccolor();
	}

	MonitorCell(Symbol Smb)
	{
        csymbol = Smb;
        Color ccolor();
	}

	MonitorCell(Symbol Smb, Color Clr)
	{
		csymbol = Smb;
		ccolor = Clr;
	}

	void replaceSymbol(Symbol Smb)
	{
		csymbol = Smb;
	}

	void replaceColor(Color Clr)
	{
		ccolor = Clr;
	}

	Symbol applyColor()
	{
		return ccolor.mapTo(csymbol);
	}

};


const MonitorCell TerminateCell(Symbol("\0"), Color());     // Special cells
const MonitorCell EmptyCell(Symbol("\s"), Color());



class Monitor
{
public:

	Terminal term;
	WriteStream writeSt;
	MonitorCell* grid;
	int current = 0;
	int curWidth = 1;
	int stopPosition;
	int maxGridSize;

    Monitor(Terminal Term, WriteStream WriteSt, int MaxGridSize)
    {
    	// if (MaxGridSize <= 0) throw MonitorError("Incorrect value of maxGridSize");
    	term = Term;
    	writeSt = WriteSt;
        grid = new MonitorCell[MaxGridSize];
        stopPosition = MaxGridSize;
        maxGridSize = MaxGridSize;
    }

								                    //## Size ##//

    void setWidth(int Wd)
    {
        curWidth = Wd;
    }

    void setEnd(int EndP)
    {
    	// if (EndP <= 0) throw MonitorError("Incorrect value");
    	// if (EndP >= maxGridSize) throw GridOverflow;
    	stopPosition = EndP;
    }

    void setHeight(int Ht)
    {
    	setEnd(curWidth*Ht);
    }

								          //## Navigating ##//

	void toStart()
    {
    	current = 0;
    }

    // void operator++
	// void operator--

    void moveUp()
    {
    	current = (current-curWidth)%stopPosition;
    }

    void moveDown()
    {
    	current = (current+curWidth)%stopPosition;
    }

    void moveLeft()
    {
        if ((current%curWidth) == 0)
		{
			current--;
			moveDown();
		} else {
			current--;
		}
    }

    void moveRight()
    {
    	current++;
    	if ((current%curWidth) == 0)
		{
			moveUp();
		}
    }

								//## Working with cells ##//

    void writeCell(int Pos, MonitorCell Cell)
    {
    	// if (Pos >= stopPosition) throw GridBoundaryExit;
    	grid[Pos] = Cell;
    }

    void writeCell2(int x, int y, MonitorCell Cell)
    {
    	writeCell(x+y*curWidth, Cell);
    }

    MonitorCell getCell(int Pos)
    {
		// if (Pos >= stopPosition) throw GridBoundaryExit;
    	return grid[Pos];
    }

    MonitorCell getCell2(int x, int y)
    {
    	return getCell(x+y*curWidth);
    }

    void writeCur(MonitorCell Cell)
    {
    	writeCell(current, Cell);
    }

	MonitorCell getCur()
    {
    	if (current >= stopPosition) return TerminateCell;
    	return grid[current];
    }

    int pushCell(MonitorCell Cell)
    {
    	if (current >= stopPosition) return 1;
    	grid[current] = Cell;
    	current++;
    	if (current == stopPosition)
		{
			toStart();
			return 1;
    	}
    	return 0;
    }

	MonitorCell slideCell()
    {
    	if (current >= stopPosition) return TerminateCell;
    	return grid[current++];
    }

								            //## Output ##//

    void clearGrid()
    {
    	toStart();
        while (!pushCell(EmptyCell));
    }

    int update()
    {
        toStart();
    	setWidth(term.getWidth());
    	setHeight(term.getHeight());
    	return 0;
    }

    int print()
    {
    	int t;
        while (true)
		{
			t = writeSt.print(slideCell().applyColor());
			if (t!=0) break;
			if ((current%curWidth) == 0) writeSt.newLine();
		}

		return 0;
    }

    int draw()
    {
    	update();
    	writeSt.clearScreen();
    	print();
    	return 0;
    }

};
>>>>>>> First commit
