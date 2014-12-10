
#include "windows.h"

//#using <mscorlib.dll>
#include <tchar.h>

//using namespace System;

//#using <System.Windows.Forms.dll>
//using namespace System::Windows::Forms;

//#using <System.dll>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"



//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main()
{
	GameEngine ge;

	ge.run();

	return (0);
}