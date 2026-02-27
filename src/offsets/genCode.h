#pragma once
#include <cstdint>
#include "../utils/geom.h"



class Player
{
public:
    void* vtable;           // 0x0000
    Vector3 o;              // 0x0004
    Vector3 velocity;       // 0x0010
    Vector3 N00000184;      // 0x001C
    Vector3 pos;            // 0x0028
    float yaw;              // 0x0034
    float pitch;            // 0x0038
    float roll;             // 0x003C
    char pad_0040[16];      // 0x0040
    float eyeHeight;        // 0x0050
    char pad_0054[152];     // 0x0054

    int32_t health;         // 0x00EC
    int32_t armor;          // 0x00F0

    char pad_00F4[56];      // 0x00F4 (Рассчитано: 0x12C - 0x00F4)

    
    int32_t pistolAmmo;     // 0x012C
    char pad_0130[4];       // 0x0130
    int32_t shotgunAmmo;    // 0x0134
    int32_t smgAmmo;        // 0x0138
    int32_t sniperAmmo;     // 0x013C
    int32_t rifleAmmo;      // 0x0140
    int32_t grenadeAmmo;    // 0x0144

    char pad_0148[16];      // 0x0148 (Рассчитано: 0x158 - 0x0148)

    
    int32_t shotgunDelay;   // 0x0158
    char pad_015C[4];       // 0x015C
    int32_t sniperDelay;    // 0x0160
    int32_t rifleDelay;     // 0x0164

    char pad_0168[156];     // 0x0168 (Рассчитано: 0x0204 - 0x0168)

    int8_t autoShoot;       // 0x0204 
    char name[104];         // 0x0205

    char pad_026D[159];     // 0x026D
    int8_t team;            // 0x030C
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