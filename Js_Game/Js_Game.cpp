

#include "Js_Game.h"
#include "Js_Core.h"
#include "Js_DxObject.h"

using namespace Js;

class Sample : public Core
{
public:
    Sample() 
    {
    }

    void Init()
    {
        obj = std::make_shared<DxObject>(GetDevice(), GetContext());
        obj->Init();
    }
    void Update()
    {

    }
    void Render()
    {

    }
    void Release()
    {

    }

private:
    std::shared_ptr<DxObject> obj;
};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   Sample core;

    if (core.CreateWin(hInstance, g_Width, g_Height))
    {
        core.GameRun();
    }
}

//class Sample : public Core {};
//GAME_START(g_Width, g_Height);
