#include "std.h"
#include "Js_Core.h"
#include "Js_Actor.h"
#include "Js_GameObject.h"
#include "Js_Time.h"
#include "Js_Input.h"

using namespace Js;


class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        RECT rt = { 0, 0, 100, 100 };
        player = std::make_shared<Actor>(GetDevice(), GetContext());
        player->CreateObject(rt, L"dopa.jpg");
    }
    void Update() override
    {
        //Vector3 scale = { cos(Time::GetGameTime()) * 0.5f + 0.5f,
        //                  cos(Time::GetGameTime()) * 0.5f + 0.5f, 
        //                  0 };
        //Vector3 center = { - 400, -300 , 0 };


        //Matrix matCenter = Matrix::CreateTranslation(center);
        //Matrix MatScale = Matrix::CreateScale(1);
        //Matrix MatRotate = Matrix::CreateRotationX(0);
        //MatRotate *= Matrix::CreateRotationY(0);
        //MatRotate *= Matrix::CreateRotationZ(0);
        //Matrix MatTranslation = Matrix::CreateTranslation(400,300,0);

        //Matrix matWorld = matCenter * MatScale * MatRotate * MatTranslation;
        //player->SetWorld(matWorld);
        if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
        {
            player->Move({ 0.0f, -1.0f, 0 });
        }
        if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
        {
            player->Move({ 0.0f, 1.0f, 0 });
        }
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            player->Move({ -1.0f, 0.0f, 0 });
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            player->Move({ 1.0f, 0.0f, 0 });
        }
        std::string pos;
        pos += "X = " + std::to_string(player->GetPosition().x) + " Y = " + std::to_string(player->GetPosition().y) + "\n";
        OutputDebugStringA(pos.c_str());

        player->Update();
    }
    void Render() override
    {
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
