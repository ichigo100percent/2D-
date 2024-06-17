#include "std.h"
#include "Js_Core.h"
#include "Js_Actor.h"
#include "Js_GameObject.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_Camera.h"

using namespace Js;

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        RECT rt1 = { 0, 0, 800, 600 };
        bg = std::make_shared<Actor>(GetDevice(), GetContext());
        bg->CreateObject(rt1, L"paka.jpg");

        RECT rt2 = { 50, 50, 100, 100 };
        player = std::make_shared<Actor>(GetDevice(), GetContext());
        player->CreateObject(rt2, L"dopa.jpg");

        // 카메라 초기 위치 설정
        camera = std::make_shared<Camera>();
        camera->SetPosition(Vector3::Zero);
    }
    void Update() override
    {
        Vector3 moveDirection = { 0.0f, 0.0f, 0.0f };

        if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
        {
            player->Move({ 0.0f, -1.0f, 0.f });
        }
        if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
        {
            player->Move({ 0.0f, 1.0f, 0.f });
        }
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            player->Move({ -1.0f, 0.0f, 0.f });
            camera->Right(-player->GetOffset().x);
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            player->Move({ 1.0f, 0.0f, 0.f });
            //hero.Right();		
            camera->Right(-player->GetOffset().x);
        }
        player->SetRotate(Time::GetGameTime());

        std::string pos;
        pos += "X = " + std::to_string(player->GetPosition().x) + " Y = " + std::to_string(player->GetPosition().y) + "\n";
        OutputDebugStringA(pos.c_str());

        camera->Update();
        bg->Update();
        player->Update();
    }
    void Render() override
    {
        bg->SetTransform(camera->GetMatrix());
        bg->Render();

        player->SetTransform(camera->GetMatrix());
        player->Render();
    }
    void Release() override
    {

    }
private:

private:
    std::shared_ptr<Actor> bg;
    std::shared_ptr<Actor> player;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Actor>> objects; // 모든 객체들을 저장
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
