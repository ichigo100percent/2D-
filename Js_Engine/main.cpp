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
        JsRect rt(g_Width / 2, g_Height/2, 100, 100);
        //obj->Init(rt, L"원희.png");
        obj->CreateObject(Vector2(400, 300), L"원희.png");
    }
    void Update() override
    {
        //obj->Update();
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

GAME_START(g_Width, g_Height);

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
