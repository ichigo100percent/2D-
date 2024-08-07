﻿#include "std.h"
#include "Js_Core.h"
#include "Js_PlayerObject.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_Camera.h"
#include "Js_Collision.h"
#include "Js_TextureMgr.h"
#include "Js_ShaderMgr.h"
#include "Js_SoundMgr.h"
#include "Js_Sprite.h"


using namespace Js;

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        bgSound = SOUND.Load(L"overworld.wav");
        if (bgSound)
        {
            bgSound->Play(true);
        }
        {
            RECT rt1 = { 0, 0, 2500, 600 };
            bg = std::make_shared<Actor>(GetDevice(), GetContext());
            bg->CreateObject(rt1, L"bg_blue.jpg");
        }
        {
            std::wstring texPath = L"../../Res/";
            for (int i = 0; i < 10; i++)
            {
                std::wstring texFileName = texPath + std::to_wstring(i) + L".bmp";
                std::shared_ptr<Texture> tex = TEXTURE.Load(texFileName);
                m_objNumberTex.push_back(tex->m_ShaderResourceView);
            }

            ui.resize(4);
            RECT rt[4] =
            {
                {0,0,50,50},
                {750,0,800,50},
                {0,430,50,480},
                {750,430,800,480},
            };
            for (int i = 0; i < ui.size(); i++)
            {
                ui[i] = std::make_shared<Actor>(GetDevice(), GetContext(), std::to_wstring(i));
                ui[i]->CreateObject(rt[i], L"dopa.jpg");
            }
        }
        {
            RECT rt2 = { 400, 300, 450, 380 };
            player = std::make_shared<PlayerObject>(GetDevice(), GetContext());
            player->CreateObject(rt2, L"dopa.jpg");
            auto sprite = std::make_shared<Sprite>();
            sprite->Load(L"Mario_nomal.gif", Vector2(50, 0), Vector2(50, 80), 5);
            sprite->SetAnim(0.5f);
            player->SetSprite(sprite);
        }
        {
            for (int i = 0; i < 10; i++)
            {
                RECT rt3{ i * 32, 0, 32 + (32 * i), 32 };
                objects.push_back(std::make_shared<Actor>(GetDevice(), GetContext()));
                objects[i]->CreateObject(rt3, L"bg_ground01.png");
            }
            objCounter = objects.size();
        }
        {
            // 카메라 초기 위치 설정
            camera = std::make_shared<Camera>();
            camera->SetPosition(Vector3::Zero);
        }
    }
    void Update() override
    {

        // 플레이어의 위치를 업데이트
        player->Update();

        // 카메라가 플레이어를 따라 이동하도록 오프셋을 사용하여 카메라 위치를 갱신
        camera->move(player->GetOffset());
        camera->Update();

        // 배경과 오브젝트의 위치를 카메라 뷰 매트릭스를 사용하여 업데이트
        bg->SetViewTransform(camera->GetMatrix());
        bg->Update();

        for(auto& obj : objects)
        {
            if (obj->GetActive() && Collision::RectToRect(obj->GetRect(), player->GetRect()))
            {
                obj->SetActive(false);
                objCounter = max(1, objCounter - 1);
            }
        }

        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->Update();
        }
        for (auto& obj : ui)
        {
            obj->Update();
        }
    }
    void Render() override
    {
        bg->SetViewTransform(camera->GetMatrix());
        bg->Render();


        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetActive())
            {
                objects[i]->SetViewTransform(camera->GetMatrix());
                objects[i]->Render();
            }
        }
        
        auto func = [&](std::shared_ptr<Actor > ui)
            {
                ui->PreRender();
                ui->GetContext()->PSSetShaderResources(0, 1, m_objNumberTex[objCounter - 1].GetAddressOf());
                ui->PostRender();
            };
        std::for_each(std::begin(ui), std::end(ui), func);
        
        //player->SetTransform(camera->GetMatrix());
        player->SetViewTransform(camera->GetMatrix());
        player->Render();
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

    std::vector<std::shared_ptr<Actor>> ui;
    UINT objCounter = 0;
    std::vector<ComPtr<ID3D11ShaderResourceView>> m_objNumberTex;
    std::shared_ptr<Sound> bgSound;
    std::shared_ptr<Sound> effectSound;
};

GAME_START(g_Width, g_Height);

/*
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
*/