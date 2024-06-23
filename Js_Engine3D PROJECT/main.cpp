#include "std.h"
#include "Js_Core.h"
#include "Js_DxObject.h"
#include "TestObject.h"
#include "Js_Collision.h"

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
        obj = std::make_shared<DxObject>(GetDevice(), GetContext(), L"player");
        obj->SetScale(Vector3(.5f, .5f, 1));
        obj->Init(L"dopa.jpg");

        
        t = std::make_shared<TestObject>(GetDevice(), GetContext());
        t->SetScale(Vector3(.3f, .3f, 1));
        t->Init(L"dopa.jpg");
    }
    void Update() override
    {
        obj->Update();
        t->Update();
        if (CheckCollision(obj->GetAABB(), t->GetAABB())) 
        {    
            OutputDebugStringA("Collision detected!\n");
        }

    }
    void Render() override
    {
        obj->Render(m_Pipeline);

        t->Render(m_Pipeline);
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<DxObject> obj;
    std::shared_ptr<TestObject> t;
};

GAME_START(g_Width, g_Height);