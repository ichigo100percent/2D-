//#include "pch.h"
#include "Js_Game.h"
#include "Js_Core.h"


using namespace Js;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    Core core;

    if (core.CreateWin(hInstance,g_Width, g_Height))
    {
        core.GameRun();
    }
}

//class Sample : public Core {};
//GAME_START(g_Width, g_Height);
