#include "esp.h"
#include "constants.h"
#include <stdio.h>
#include "geom.h"
#include "settings.h"
#include "imgui/imgui.h"
#include <iostream>

const float FOV = 90;

//void normalizeAngle(vec3& angle) {
//	if (angle.x > 360)
//		angle.x -= 360;
//	if (angle.x < 360)
//		angle.x += 360;
//	if (angle.y > 90)
//		angle.x -= 90;
//	if (angle.x > -90)
//		angle.x -= 90;
//
//	
//
//}
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

Player* ESP::getNearestEntityAngle()
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
void drawCenterText(std::string text, float x, float y) {
	float textWidth = ImGui::CalcTextSize(text.c_str()).x;
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - textWidth, y), IM_COL32(1, 1, 100, 255), text.c_str());

}
void drawScallingBar(float x1,float y1, float x2,float width, float y2,float val,float max,ImColor color){
	float widthDiff = x2 - x1;
	float heightDiff = y2 - y1;
	float scalledHeight = heightDiff * (val / max);
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), IM_COL32(1, 1, 100, width));
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y1+ scalledHeight), IM_COL32(1, 1, 100, color));




}
void ESP::drawESP()
{	
	if (!Settings::ESP::enabled)
		return;
	bool teammate = false;
	Player* player = nullptr;
	for (int i = 1; i < numPlayers; i++) {
		player = players->players[i];
		if (player->health > 100 or player->health < 0)
			continue;
		teammate = player->team == localPlayerPtr->team;
		if (teammate and !Settings::ESP::drawTeam)
			continue;
		vec3 headPos = { player->o.x,player->o.y,player->o.z };
		vec3 feetPos = { player->o.x,player->o.y,player->o.z- player->eyeHeaight };
		vec3 headScreenPose = OpenGLWorldToScreen(headPos);
		vec3 feetScreenPose = OpenGLWorldToScreen(feetPos);
		

		float height = abs(headScreenPose.y - feetScreenPose.y);
		float width = height / 2;
		ImVec2 topLeft = ImVec2(feetScreenPose.x - width, headScreenPose.y);
		ImVec2 topRight= ImVec2(feetScreenPose.x + width, headScreenPose.y);
		ImVec2 bottomLeft = ImVec2(feetScreenPose.x - width, feetScreenPose.y);
		ImVec2 bottomRight = ImVec2(feetScreenPose.x + width, feetScreenPose.y);

		ImColor currColor = teammate ? *Settings::ESP::enemyColor : *Settings::ESP::mateColor;

		ImGui::GetBackgroundDrawList()->AddQuad(topLeft, bottomLeft, bottomRight, topRight, currColor, 1.0f);
		//drawScallingBar(bottomLeft.x - 5, -width / 2, bottomLeft.y, bottomLeft.x - 5, topRight.y, 1,100, ImColor(255,0,0,255));

	}

}
