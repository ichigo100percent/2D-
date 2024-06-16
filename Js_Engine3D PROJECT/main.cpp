#include "std.h"
#include "Js_Core.h"
#include "Js_GameObject.h"

using namespace Js;

class Sample : public Core
{
public:
    Sample() {}
    ~Sample() {}

    void Init() override
    {
        obj = std::make_shared<GameObject>(GetDevice(), GetContext(), L"player");
        obj->CreateObject(L"dopa.jpg");
        obj->SetPosition(Vector3(0.f, 0.f, 0));
    }
    void Update() override
    {
        obj->Update();
    }
    void Render() override
    {
        obj->Render();
    }
    void Release() override
    {

    }
private:
    std::shared_ptr<GameObject> obj;
};

GAME_START(g_Width, g_Height);