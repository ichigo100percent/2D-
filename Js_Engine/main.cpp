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
        RECT rt = { 0, 0, 100, 100 };
        player = std::make_shared<Actor>(GetDevice(), GetContext());
        player->CreateObject(rt, L"dopa.jpg");

        // 카메라 초기 위치 설정
        camera = std::make_shared<Camera>();

    }
    void Update() override
    {
        Vector3 moveDirection = { 0.0f, 0.0f, 0.0f };

        if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
        {
            moveDirection.y -= 1.0f;
        }
        if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
        {
            moveDirection.y += 1.0f;
        }
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            moveDirection.x -= 1.0f;
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            moveDirection.x += 1.0f;
        }

        player->Move(moveDirection);



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

private:
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
