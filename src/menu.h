#pragma once
#include <Windows.h>

namespace Menu {
	void toggleMenu();
	void init();
	void startRender();
	void endRender();


	void render();
	


}
BOOL __stdcall newSwapBuffers(HDC hdc);