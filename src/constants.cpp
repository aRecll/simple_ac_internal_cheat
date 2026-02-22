#include "constants.h"
#include <cstdint>

HMODULE hModule=GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

Player* localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
uintptr_t playersAddr = exeBaseAddress + 0x18AC04;
EntityList* players = *(EntityList**)(playersAddr);
int numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);
float* viewMatrix= reinterpret_cast<float*>(exeBaseAddress + 0x17DFD0);
AppResolution* thisResolution = reinterpret_cast<AppResolution*>(exeBaseAddress + 0x191ED8);

_wglSwapBuffers originalSwapBuffers= (_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
_SDL_SetRelativeMouseMode originalSetRelativeMouseMode = (_SDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));
tClipCursor oClipCursor = (tClipCursor)GetProcAddress(GetModuleHandle(L"user32.dll"), "ClipCursor");
tSetCursorPos oSetCursorPos = (tSetCursorPos)GetProcAddress(GetModuleHandle(L"user32.dll"), "SetCursorPos");



void resertPointers()
{
    localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
    players = *reinterpret_cast<EntityList**>(exeBaseAddress + 0x18AC04);
    numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);
    thisResolution= reinterpret_cast<AppResolution*>(exeBaseAddress + 0x191ED8);
    viewMatrix = reinterpret_cast<float*>(exeBaseAddress + 0x17DFD0);
}
