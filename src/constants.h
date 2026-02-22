#pragma once
#include <windows.h>
#include <vector>
#include "genCode.h"

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;
extern Player* localPlayerPtr;
extern EntityList* players;
extern int numPlayers;
extern float* viewMatrix;
extern AppResolution* thisResolution;
void resertPointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;

typedef int(__fastcall* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode originalSetRelativeMouseMode;

typedef BOOL(WINAPI* tSetCursorPos)(int, int);
extern tSetCursorPos oSetCursorPos;

typedef BOOL(WINAPI* tClipCursor)(const RECT* lpRect);
extern tClipCursor oClipCursor;


