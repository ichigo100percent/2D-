#include "std.h"
#include "Js_Core.h"
//#include "Js_DxObject.h"
#include "Js_GameObject.h"
using namespace Js;

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        obj = std::make_shared<DxObject>(GetDevice(), GetContext(), L"player");
        bg = std::make_shared<GameObject>(GetDevice(), GetContext(), L"BackGround");
        obj->CreateObject(Vector2(400, 300), L"dopa.jpg");
        bg->CreateObject(Vector2(0, 0), L"paka.jpg");
    }
    void Update() override
    {
        obj->Update();

    }
    void Render() override
    {
        bg->Render();
        obj->Render();
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<DxObject> obj;
    std::shared_ptr<GameObject> bg;
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
