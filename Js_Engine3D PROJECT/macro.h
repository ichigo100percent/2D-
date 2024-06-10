#pragma once

#define CHECK(p)	assert(SUCCEEDED(p))

#define SAMPLE_CREATE class Sample : public Core {
#define SAMPLE_END };
#define GAME_START(x, y) int WINAPI wWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,PWSTR pCmdLine,int nCmdShow){	Sample win;	if (win.CreateWin(hInstance, x, y))	{		win.GameRun();	}	return 0;}
#define GAME(x,y)  SAMPLE_CREATE SAMPLE_END GAME_START(x,y)