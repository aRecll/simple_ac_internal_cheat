#include "computingfunc.h"
#include "../offsets/constants.h"
#include "../menu/settings.h"
#include <ctime>

float curAimTime = 0;
clock_t lastAimTime = clock();
Player* curTarget = nullptr;
bool isInFov(Player* owner, Vec3 looking) {
	vec3 angle = CalcAngle(owner->pos, looking);
	vec3 playerAngle(owner->yaw + 100, owner->pitch, 0);
	playerAngle.NormalizeAngle();
	//normalizeAngle(playerAngle);
	vec3 angleDiff = playerAngle - angle;
	//normalizeAngle(angleDiff);
	angleDiff.NormalizeAngle();
	float deviation = sqrt(pow(angleDiff.x, 2) + pow(angleDiff.y, 2));

	return (deviation <= FOV / 2);
}
bool isValidTarget(Player* player) {


	if (player == nullptr )
		return false;


	if (player == localPlayerPtr)
		return false;

	if (player->team == localPlayerPtr->team ) {
		return false;
	}


	if (player->health <= 0 || player->health > 1000)
		return false;


	 //if(!isInFOV(localPlayerPtr, player->o))
		//	return false;



	return true;
}

bool isInFovWS2(vec3 screenLoc)
{	
	if (abs(centerScreenPos.Distance(screenLoc)) < Settings::Aimbot::fov)
		return true;
	return false;
}

void smoothAngel(vec& from, vec& to, float percent)
{
	
	vec3 delta = to - from;

	
	while (delta.x > 180.0f)  delta.x -= 360.0f;
	while (delta.x < -180.0f) delta.x += 360.0f;

	
	if (delta.y > 89.0f) delta.y = 89.0f;
	if (delta.y < -89.0f) delta.y = -89.0f;

	
	if (percent > 1.0f) percent = 1.0f;
	if (percent < 0.0f) percent = 0.0f;

	from.x += delta.x * percent;
	from.y += delta.y * percent;

	
	if (from.x >= 360.0f) from.x -= 360.0f;
	if (from.x < 0.0f)    from.x += 360.0f;

	if (from.y > 89.0f)  from.y = 89.0f;
	if (from.y < -89.0f) from.y = -89.0f;
}

Player* getNearestEntityWS2()
{	
	Player* nearestPlayer = nullptr;
	float nearestDistance = 9999999.0f;
	float distance = 0;
	for (int i = 1; i < numPlayers; i++) {
		Player* player = players->players[i];
		if (!isValidTarget(player))
			continue;
		vec3 headPos = { player->o.x,player->o.y ,player->o.z };
		vec3 headScreeenPos= OpenGLWorldToScreen(headPos);
		if (headScreeenPos.z < 0)
			continue;
		if (Settings::Aimbot::checkInFov and !isInFovWS2(headScreeenPos))
			continue;
		headScreeenPos.z = 0;
		distance = abs(centerScreenPos.Distance(headScreeenPos));
		if (distance < nearestDistance) {
			nearestDistance = distance;
			nearestPlayer = player;
		}

	}
	return nearestPlayer;

	
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
		if (!isValidTarget(player))
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