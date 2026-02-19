#pragma once
#include <cstdint>
#include "geom.h"



class Player
{
public:
    void* vtable;
    Vector3 o;          // 0x0004
    Vector3 velocity;   // 0x0010
    Vector3 N00000184;  // 0x001C
    Vector3 pos;        // 0x0028
    float yaw;          // 0x0034
    float pitch;        // 0x0038
    float roll;         // 0x003C
    char pad_0040[172]; // 0x0040
    int32_t health;     // 0x00EC
    char pad_00F0[278]; // 0x00F0
    int8_t N00000315;   // 0x0206
    char pad_0207[261]; // 0x0207
    int32_t team;       // 0x030C
};

class EntityList {
public:
    Player* players[64];
};