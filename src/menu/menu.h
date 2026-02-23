#pragma once
#include <Windows.h>

namespace Menu {
	void toggleMenu();
	void init(HDC hdc);
	void startRender();
	void endRender();


	void render();
	


}
BOOL __stdcall newSwapBuffers(HDC hdc);
BOOL WINAPI hClipCursor(const RECT* lpRect);
BOOL WINAPI hSetCursorPos(int X, int Y);