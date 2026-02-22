#include "constants.h"
#include <cstdint>

HMODULE hModule=GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

extern Player* localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
uintptr_t playersAddr = exeBaseAddress + 0x18AC04;
extern EntityList* players = *(EntityList**)(playersAddr);
extern int numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);



_wglSwapBuffers originalSwapBuffers= 
(_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");


_SDL_SetRelativeMouseMode originalSetRelativeMouseMode = 
(_SDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));

//tSetCursorPos oSetCursorPos = (tSetCursorPos)GetProcAddress(GetModuleHandle(L"user32.dll"), "tSetCursorPos");

tClipCursor oClipCursor = 
(tClipCursor)GetProcAddress(GetModuleHandle(L"user32.dll"), "ClipCursor");


tSetCursorPos oSetCursorPos = 
(tSetCursorPos)GetProcAddress(GetModuleHandle(L"user32.dll"), "SetCursorPos");
void resertPointers()
{
    localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
    players = *reinterpret_cast<EntityList**>(exeBaseAddress + 0x18AC04);
    numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);
}
