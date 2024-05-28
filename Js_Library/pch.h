#pragma once


#include "framework.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm> 
#include <assert.h>
#include <tchar.h>


#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include "SimpleMath.h"
#include "DirectXTex.h"
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

const int g_Width = 800;
const int g_Height = 600;

using namespace Microsoft::WRL;

#define CHECK(p)	assert(SUCCEEDED(p))

class BaseCore
{
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

#define SAMPLE_CREATE class Sample : public Core {
#define SAMPLE_END };
#define GAME_START(x, y) int WINAPI wWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,PWSTR pCmdLine,int nCmdShow){	Sample win;	if (win.CreateWin(hInstance, x, y))	{		win.GameRun();	}	return 0;}
#define GAME(x,y)  SAMPLE_CREATE SAMPLE_END T_GAME_START(x,y)