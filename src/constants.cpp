#include "constants.h"
#include <cstdint>

HMODULE hModule=GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

extern Player* localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
uintptr_t playersAddr = exeBaseAddress + 0x18AC04;
extern EntityList* players = *(EntityList**)(playersAddr);
extern int numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);





void resertPointers()
{
    localPlayerPtr = *reinterpret_cast<Player**>(exeBaseAddress + 0x0017E0A8);
    players = *reinterpret_cast<EntityList**>(playersAddr);
    numPlayers = *reinterpret_cast<int*>(exeBaseAddress + 0x18AC0C);
}
