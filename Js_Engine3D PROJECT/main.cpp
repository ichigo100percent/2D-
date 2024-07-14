#include "std.h"
#include "Js_Core.h"

using namespace Js;

class Sample : public Core {};

//GAME_START(g_Width, g_Height);


int WINAPI wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR pCmdLine,
    int nCmdShow)
{
    Sample core;

    if (core.CreateWin(hInstance, g_Width, g_Height))
    {
        core.GameRun();
    }
    return 0;
};