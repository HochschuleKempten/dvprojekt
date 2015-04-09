// ------------------------------------------------------------------------
// See http://dslweb.nwnexus.com/~ast/dload/guicon.htm for more information
// ------------------------------------------------------------------------

#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>

using namespace std;

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

#ifdef _DEBUG

void RedirectIOToConsole() {

	int hConsoleHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	FILE* pFile;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	consoleInfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), consoleInfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long) GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	pFile = _fdopen(hConsoleHandle, "w");
	*stdout = *pFile;
	setvbuf(stdout, NULL, _IONBF, 0);
}

#endif