//#include "pch.h"
#include "Js_Game.h"
#include "Js_Core.h"


using namespace Js;

//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    Core core;
//
//    core.CreateRegisterClass(hInstance);
//
//    if (core.InitInstance(g_Width, g_Height))
//    {
//        core.Run();
//    }
//}

class Sample : public Core {};
GAME_START(800, 600);
