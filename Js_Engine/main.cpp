#include "std.h"
#include "Js_Core.h"
#include "Js_PlayerObject.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_Camera.h"
#include "Js_Collision.h"

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
        bg->CreateObject(rt1, L"bg_blue.jpg");

        RECT rt2 = { 400, 300, 450, 380 };
        player = std::make_shared<PlayerObject>(GetDevice(), GetContext());
        player->CreateObject(rt2, L"bitmap1Alpha.bmp");

    
        for (int i = 0; i < 10; i++)
        {
            RECT rt3{ i * 32, 0, 32 + (32 * i), 32 };
            objects.push_back(std::make_shared<Actor>(GetDevice(), GetContext()));
            objects[i]->CreateObject(rt3, L"bg_ground01.png");
        }

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
            camera->Up();
        }
        if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
        {
            player->Move({ 0.0f, 1.0f, 0.f });
            camera->Down();
        }
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            player->Move({ -1.0f, 0.0f, 0.f });
            camera->Right(-player->GetOffset().x);
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            player->Move({ 1.0f, 0.0f, 0.f });
            camera->Right(-player->GetOffset().x);
        }

        for(auto& obj : objects)
        {
            if (obj->GetActive() && Collision::RectToRect(obj->GetRect(), player->GetRect()))
            {
                obj->SetActive(false);
                // count --;
            }
        }

        //std::string pos;
        //pos += "X = " + std::to_string(player->GetPosition().x) + " Y = " + std::to_string(player->GetPosition().y) + "\n";
        //OutputDebugStringA(pos.c_str());
        std::string rt;
        rt += "left = " + std::to_string(player->GetRect().left) + " top = " + std::to_string(player->GetRect().top) + "\n";
        rt += "right = " + std::to_string(player->GetRect().right) + " bottom = " + std::to_string(player->GetRect().bottom) + "\n";
        OutputDebugStringA(rt.c_str());

        camera->Update();
        bg->Update();
        player->Update();
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->Update();
        }
    }
    void Render() override
    {
        bg->SetTransform(camera->GetMatrix());
        bg->Render();

        player->SetTransform(camera->GetMatrix());
        player->Render();

        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetActive())
            {
                objects[i]->SetTransform(camera->GetMatrix());
                objects[i]->Render();
            }
        }
    }
    void Release() override
    {

    }
private:

private:
    std::shared_ptr<Actor> bg;
    std::shared_ptr<PlayerObject> player;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Actor>> objects; // 모든 객체들을 저장
};

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
