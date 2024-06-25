#include "std.h"
#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_DxObject.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_Camera.h"

// Scripts
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"

#include "TestObject.h"

using namespace Js;


bool CheckCollision(const MyRect& rect1, const MyRect& rect2)
{
    // 두 사각형이 충돌하는지 확인
    if (rect1.left < rect2.right &&
        rect1.right > rect2.left &&
        rect1.top > rect2.bottom &&
        rect1.bottom < rect2.top)
    {
        return true; // 충돌 발생
    }
    return false; // 충돌 없음
}

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        camera = std::make_shared<DxObject>(GetDevice(), GetContext());
        {
            camera->GetOrAddTransform();
            camera->AddComponent(std::make_shared<Camera>());
            camera->AddComponent(std::make_shared<MoveScript>());
            camera->Init();
        }
        bg = std::make_shared<DxObject>(GetDevice(), GetContext(), L"bg_blue.jpg");
        {
            bg->GetOrAddTransform()->SetScale(bg->GetSize());
            bg->Init();
        }

        player = std::make_shared<DxObject>(GetDevice(), GetContext(), L"1.bmp");
        {
            player->AddComponent(std::make_shared<MoveScript>());
            player->GetOrAddTransform()->SetScale(player->GetSize());
            player->Init();
        }
        t = std::make_shared<TestObject>(GetDevice(), GetContext(), L"1.bmp");
        {
            t->GetOrAddTransform()->SetScale(player->GetSize());
            t->Init();
        }
    }
    void Update() override
    {
        camera->Update();
        bg->Update();
        player->Update();
        t->Update();
    }
    void LateUpdate() override
    {
		if (CheckCollision(player->GetTransform()->GetRect(), t->GetTransform()->GetRect()))
		{
            OutputDebugStringA("Collision detected!\n");
		}
        player->LateUpdate();
        t->LateUpdate();
    }
    void Render() override
    {
        camera->Render(m_Pipeline);
        bg->Render(m_Pipeline);
        player->Render(m_Pipeline);
        t->Render(m_Pipeline);
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<DxObject> camera;
    std::shared_ptr<DxObject> bg;
    std::shared_ptr<DxObject> player;
    std::shared_ptr<TestObject> t;
};

GAME_START(g_Width, g_Height);