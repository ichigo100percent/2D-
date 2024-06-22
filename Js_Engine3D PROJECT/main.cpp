#include "std.h"
#include "Js_Core.h"
#include "Js_DxObject.h"
#include "TestObject.h"
#include "Js_Collision.h"

using namespace Js;


bool CheckCollision(const MyRect& a, const MyRect& b) {
    return (a.left < b.right && a.right > b.left && a.top > b.bottom && a.bottom < b.top);
}

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        obj = std::make_shared<DxObject>(GetDevice(), GetContext(), L"player");
        obj->CreateObject(L"dopa.jpg");
        
        t = std::make_shared<TestObject>(GetDevice(), GetContext());
        t->CreateObject(L"dopa.jpg");

    }
    void Update() override
    {
        if (CheckCollision(obj->GetAABB(), t->GetAABB())) {
          
            OutputDebugStringA("Collision detected!\n");
        }

        obj->Update();
        t->Update();
    }
    void Render() override
    {
        obj->Render();

        t->Render();
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<DxObject> obj;
    std::shared_ptr<TestObject> t;
};

GAME_START(g_Width, g_Height);