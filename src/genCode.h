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
    char pad_0040[16]; // 0x0040
    float eyeHeaight;     // 0x0050
    char pad_0054[152]; // 0x0054
    int32_t health; // 0x00EC
    char pad_00F0[277];// 0x00F0
    char name[104];   // 0x0205
    char pad_026D[159]; // 0x026D
    int8_t team;       // 0x030C
};

class EntityList {
public:
    Player* players[64];
};

class AppResolution {
public:
    int32_t windowWidth;
    int32_t windowHeight;
    

};