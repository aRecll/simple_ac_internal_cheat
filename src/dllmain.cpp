#include <iostream>
#include <windows.h>
#include "menu/menu.h"
#include "offsets/constants.h"
#include "offsets/genCode.h"
#include "features/esp.h"
#include "detours/detours.h"
#include "utils/support.h"
#include "features/aimbot.h"
#include "features/changestats.h"
//#pragma comment(lib, "detours.lib")
//#define DEBUG


void hook() {
    Sleep(1000);
    DisableThreadLibraryCalls(hModule);
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)originalSwapBuffers, newSwapBuffers);
    DetourAttach(&(PVOID&)oClipCursor, hClipCursor);
    DetourAttach(&(PVOID&)oSetCursorPos, hSetCursorPos);

    DetourTransactionCommit();
#ifdef _DEBUG
    std::cout << "hook are complited" << std::endl;
#endif
    while (1) {
        resertPointers();
        if (Settings::Stats::infinityAmmo or Settings::Stats::infinityHealt) {
            updateStats();
        }
       updateFOV();
       updateSpeedOfShuts();
        
        Sleep(50);
        if (IsKeyPressed(VK_DELETE)) {
            Menu::toggleMenu();
        }

    }
   //std::cout << thisResolution->windowHeight << std::endl;


}
void forDebug() {
    while (1) {
        resertPointers();
        
       // ESP::aimbot();
        Sleep(50);
        if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
            Menu::toggleMenu();
        }
    }


}
void console() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
#ifdef _DEBUG
    std::cout << "Console Created." << std::endl;
#endif
    while (1) {
        std::cout << localPlayerPtr->shotgunDelay << std::endl;
        std::cout << localPlayerPtr->rifleDelay << std::endl;
        std::cout << localPlayerPtr->sniperDelay << std::endl;
        std::cout << "\n\n\n\n\n" << std::endl;
    }
    
    FreeConsole();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
       
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
       // CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, nullptr, 0, nullptr);
#ifdef _DEBUG
        
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
#endif // DEBUG

       
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}