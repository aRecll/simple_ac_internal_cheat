#pragma once
#include <windows.h>
#include <vector>
#include "genCode.h"

extern HMODULE hMODULE;
extern uintptr_t exeBaseAddress;
extern Player* localPlayerPtr;
extern EntityList* players;
extern int numPlayers;

void resertPointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;

typedef int(__stdcall* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode oroginalSetRelativeMouseMode;