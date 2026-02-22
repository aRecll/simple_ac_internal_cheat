#include <iostream>
#include <windows.h>
#include "menu.h"
#include "constants.h"
#include "genCode.h"
#include "esp.h"
#include "detours/detours.h"

//#pragma comment(lib, "detours.lib")
//#define DEBUG

void aimbot() {

    while (1) {
        resertPointers();
        ESP::aimbot();
        Sleep(50);
        if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
            Menu::toggleMenu();
        }
    }
}
void hook() {
    Sleep(1000);
    DisableThreadLibraryCalls(hModule);
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)originalSwapBuffers, newSwapBuffers);
   /* DetourAttach(&(PVOID&)oClipCursor, hClipCursor);
    DetourAttach(&(PVOID&)oSetCursorPos, hSetCursorPos);*/
    DetourTransactionCommit();
   // std::cout << "he in hook\n";


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

    std::cout << "Console Created." << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::cin >> input;

        if (input == "exit") break;

       
        

        if (input == "up" ) {
            localPlayerPtr->pos.y += 5.0f;
        }
        else if (input == "down" ) {
            localPlayerPtr->pos.y -= 5.0f;
        }
        else if (input == "print") {
            std::cout << "Local Player Ptr: " << localPlayerPtr << std::endl;
        }
        else if (input == "amount") {
            std::cout << "Number of players: " << numPlayers << std::endl;
        }
        else if (input == "ent" && players) {
            for (int i = 0; i < numPlayers; i++) {
                auto entity = players->players[i];

                
                if (!entity || !entity->vtable) continue;

                std::cout << "Entity [" << i << "] Pos: "
                    << entity->pos.x << ", "
                    << entity->pos.y << ", "
                    << entity->pos.z << std::endl;
            }
        }
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
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, nullptr, 0, nullptr);
#ifdef DEBUG
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)forDebug, nullptr, 0, nullptr);
#endif // DEBUG

       
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}