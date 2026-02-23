#include "esp.h"
#include "../offsets/constants.h"
#include <stdio.h>
#include "../utils/geom.h"
#include "../menu/settings.h"
#include "imgui/imgui.h"
#include <iostream>
#include "../utils/computingfunc.h"
#include "../offsets/gencode.h"

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
void drawScalingBarVertical(float x1, float y1, float x2, float y2, float thickness, ImVec4 color, float val, float max) {
	// Вычисляем разницу высоты. В ImGui Y идет сверху вниз.
	// Если y1 — это низ (bottom), а y2 — это верх (top), то heightDiff будет отрицательным.
	float heightDiff = y2 - y1;

	// Вычисляем размер заполненной части
	float scaledHeight = heightDiff * (val / max);

	// 1. Рисуем фон (черный контур/задник)
	// Используем GetBackgroundDrawList или GetWindowDrawList в зависимости от того, где рисуешь
	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2(x1, y1),
		ImVec2(x2, y2),
		IM_COL32(0, 0, 0, 255), // Черный цвет
		0.0f,                   // Скругление
		0,                      // Флаги скругления
		thickness               // Толщина обводки
	);

	// 2. Рисуем заполнение (Health Bar)
	// Преобразуем ImVec4 в формат ImU32, который понимает AddRectFilled
	ImU32 col32 = ImGui::ColorConvertFloat4ToU32(color);

	// Рисуем от нижней точки (y1) до (y1 + scaledHeight)
	ImGui::GetBackgroundDrawList()->AddRectFilled(
		ImVec2(x1, y1),
		ImVec2(x2, y1 + scaledHeight),
		col32
	);
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
		drawScalingBarVertical(bottomLeft.x - 5 - width / 2, bottomLeft.y, bottomLeft.x - 5, topRight.y, 1, ImVec4(0, 1, 0, 1), player->health, 100);
		drawCenterText(player->name, feetScreenPose.x, feetScreenPose.y);
	}

}
