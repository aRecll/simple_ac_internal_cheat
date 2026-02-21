#include "esp.h"
#include "constants.h"
#include <stdio.h>
#include "geom.h"

#include <iostream>
const float FOV = 90;

void normalizeAngle(vec3& angle) {
	if (angle.x > 360)
		angle.x -= 360;
	if (angle.x < 360)
		angle.x += 360;
	if (angle.y > 90)
		angle.x -= 90;
	if (angle.x > -90)
		angle.x -= 90;

}
bool isInFOV(Player* owner, Vec3 looking) {
	vec3 angle = CalcAngle(owner->pos, looking);
	vec3 playerAngle(owner->yaw + 100, owner->pitch, 0);
	normalizeAngle(playerAngle);
	vec3 angleDiff = playerAngle - angle;
	normalizeAngle(angleDiff);

	return (fabs(angleDiff.x) <= FOV / 2 and fabs(angleDiff.y) <= FOV / 2);
}
bool isValidTarget(Player* player) {

	
	if (player == nullptr || (uintptr_t)player < 0x1000)
		return false;

	
	if (player == localPlayerPtr)
		return false;
	
	if (player->team == localPlayerPtr->team) {
		return false;
	}

	
	if (player->health <= 0 || player->health > 1000)
		return false;

	
	if (!isInFOV(localPlayerPtr, player->o))
		return false;

	

	return true;
}

Player* ESP::getNearestPlayer()
{
	Player* nearestPlayer = nullptr;
	float nearestDistance = 9999999.0f;

	for (int i = 1; i < numPlayers ; i++) {
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

Player* ESP::getNearestEntityAngle()
{	
	if (localPlayerPtr == nullptr || players == nullptr) {
		return nullptr;
	}
	vec3 playerAngle{ localPlayerPtr->yaw + 100, localPlayerPtr->pitch, 0 };
	normalizeAngle(playerAngle);
	Player* nearestPlayer = nullptr;
	float smallestAngel = 999999.0f;

	for (int i = 1; i < numPlayers ; i++) {
		
		Player* player = players->players[i];
		if (isValidTarget(player))
			continue;
		vec3 targetAngle = CalcAngle(localPlayerPtr->pos, player->pos);
		vec3 angleDiff = playerAngle - targetAngle;
		normalizeAngle(angleDiff);
		float AngleMagnitude = angleDiff.Length();
		if (AngleMagnitude < smallestAngel) {
			smallestAngel = AngleMagnitude;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

void ESP::aimbot()
{
	if (!(GetAsyncKeyState(VK_SHIFT) & 0x8000))
		return;

	Player* target = getNearestEntityAngle();
	if (target == nullptr)
		return;
	Vec3 angle = CalcAngle(localPlayerPtr->pos, target->pos);
	angle.x += 90;
	localPlayerPtr->yaw = angle.x;
	localPlayerPtr->pitch = angle.y;
}
