#pragma once

#include "../offsets/constants.h"
#include "geom.h"
#include <ctime>

extern float curAimTime;
extern clock_t lastAimTime;
extern Player* curTarget;
bool isInFov(Player* owner, Vec3 looking);
bool isValidTarget(Player* player);
bool isInFovWS2(vec3 screenLoc);
void smoothAngel(vec& from, vec& to, float percent);
Player* getNearestEntityWS2();
Player* getNearestPlayer();
Player* getNearestEntityAngle();