#include "std.h"
#include "Js_Core.h"
#include "Js_Actor.h"
#include "Js_GameObject.h"
using namespace Js;

class Hero : public DxObject
{
public:
    
private:
     
};

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        //obj = std::make_shared<DxObject>(GetDevice(), GetContext(), L"player");
        //obj->CreateObject(Vector2(400, 300), L"dopa.jpg");
        //bg = std::make_shared<GameObject>(GetDevice(), GetContext(), L"BackGround");
        //bg->CreateObject(Vector2(0, 0), L"paka.jpg");
        player = std::make_shared<Actor>(GetDevice(), GetContext());
        player->CreateObject(Vector2(400, 300), L"dopa.jpg");
    }
    void Update() override
    {
        //obj->Update();
        player->Update();
    }
    void Render() override
    {
        //obj->Render();
        //bg->Render();
        player->Render();
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<DxObject> obj;
    std::shared_ptr<GameObject> bg;
    std::shared_ptr<Actor> player;
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
