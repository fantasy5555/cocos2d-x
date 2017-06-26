#include "main.h"
#include "SimulatorWin.h"
#include <shellapi.h>
#pragma comment(lib, "libxreaderp.lib")
#pragma comment(lib, "libxreader.lib")

int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    auto simulator = SimulatorWin::getInstance();
    return simulator->run();
}
