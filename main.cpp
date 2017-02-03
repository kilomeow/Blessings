#include "Symbol.hpp"
#include "Monitor.hpp"
#include "TerminalFake.hpp"
#include "WriteStdIO.hpp"




int main()
{
	TerminalFake term;
	WriteStdIO wstream;

	Monitor M(term, wstream, 400);
	M.update();

	for (int i=0;i++;i<400)
	{
		M.pushCell(MonitorCell(Symbol("a"), ColorANSI(1, 1)));
	}

	M.draw();

	return 0;

}
