#include "computingfunc.h"
#include "../offsets/constants.h"

bool isInFOV(Player* owner, Vec3 looking) {
	vec3 angle = CalcAngle(owner->pos, looking);
	vec3 playerAngle(owner->yaw + 100, owner->pitch, 0);
	playerAngle.NormalizeAngle();
	//normalizeAngle(playerAngle);
	vec3 angleDiff = playerAngle - angle;
	//normalizeAngle(angleDiff);
	angleDiff.NormalizeAngle();
	return (fabs(angleDiff.x) <= FOV / 2 and fabs(angleDiff.y) <= FOV / 2);
}
bool isValidTarget(Player* player) {


	if (player == nullptr || (uintptr_t)player < 0x1000)
		return false;


	if (player == localPlayerPtr)
		return false;

	if (player->team - localPlayerPtr->team == 0) {
		return false;
	}


	if (player->health <= 0 || player->health > 1000)
		return false;


	if (!isInFOV(localPlayerPtr, player->o))
		return false;



	return true;
}

Player* getNearestPlayer()
{
	Player* nearestPlayer = nullptr;
	float nearestDistance = 9999999.0f;

	for (int i = 1; i < numPlayers; i++) {
		Player* player = players->players[i];
		if (!isValidTarget(player))
			continue;
		float distance = localPlayerPtr->pos.Distance(player->pos);
		if (distance < nearestDistance) {
			nearestDistance = distance;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

Player* getNearestEntityAngle()
{
	if (localPlayerPtr == nullptr || players == nullptr) {
		return nullptr;
	}
	vec3 playerAngle{ localPlayerPtr->yaw + 100, localPlayerPtr->pitch, 0 };
	//normalizeAngle(playerAngle);
	playerAngle.NormalizeAngle();
	Player* nearestPlayer = nullptr;
	float smallestAngel = 999999.0f;

	for (int i = 1; i < numPlayers; i++) {

		Player* player = players->players[i];
		if (isValidTarget(player))
			continue;
		vec3 targetAngle = CalcAngle(localPlayerPtr->pos, player->pos);
		vec3 angleDiff = playerAngle - targetAngle;
		//normalizeAngle(angleDiff);
		angleDiff.NormalizeAngle();
		float AngleMagnitude = angleDiff.Length();
		if (AngleMagnitude < smallestAngel) {
			smallestAngel = AngleMagnitude;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}