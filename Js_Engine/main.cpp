#include "std.h"
#include "Js_Core.h"
#include "Js_DxObject.h"


using namespace Js;

class Sample : public Core
{
public:
    Sample()
    {
    }

    void Init() override
    {
        obj = std::make_shared<DxObject>(GetDevice(), GetContext());
        obj->Init();
    }
    void Update() override
    {

    }
    void Render() override
    {
        obj->Render();
    }
    void Release() override
    {

    }

private:
    std::shared_ptr<DxObject> obj;
};


//int WINAPI wWinMain(HINSTANCE hInstance,
//    HINSTANCE hPrevInstance,
//    PWSTR pCmdLine,
//    int nCmdShow)
//{
//    Sample core;
//
//    if (core.CreateWin(hInstance, g_Width, g_Height))
//    {
//        core.GameRun();
//    }
//    return 0;
//};

GAME_START(g_Width, g_Height);