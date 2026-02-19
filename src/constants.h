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


