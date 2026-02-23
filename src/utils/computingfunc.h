#pragma once

#include "../offsets/constants.h"
#include "geom.h"

bool isInFOV(Player* owner, Vec3 looking);
bool isValidTarget(Player* player);
Player* getNearestPlayer();
Player* getNearestEntityAngle();