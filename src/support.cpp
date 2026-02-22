#include <windows.h>
#include "support.h"
bool IsKeyPressed(int vKey) {
    static bool keyState[256] = { false }; 

    if (GetAsyncKeyState(vKey) & 0x8000) {
        if (!keyState[vKey]) {
            keyState[vKey] = true;
            return true; 
        }
    }
    else {
        keyState[vKey] = false;
    }
    return false;
}


