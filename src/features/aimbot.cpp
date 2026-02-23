#include "aimbot.h"

#include "../utils/support.h"
#include "../utils/computingfunc.h"
#include "../menu/settings.h"
#include "../external/imgui/imgui.h"
#include <ctime>
#include <iostream>
void aim::aimbot()
{	
	if (Settings::Aimbot::drawFovCircle and Settings::Aimbot::checkInFov)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(centerScreenPos.x, centerScreenPos.y),
			Settings::Aimbot::fov, IM_COL32(255, 255, 255, 128), 100);
	if (!(GetAsyncKeyState(VK_SHIFT) & 0x8000) or !Settings::Aimbot::enabled) {
		curAimTime = 0;
		lastAimTime = clock();
		curTarget = nullptr;
		return;
	}
		
	


	
	Player* target = getNearestEntityWS2();
	if (!target)
		return;
	if (target!=curTarget) {
		curAimTime = 0;
		lastAimTime = clock();
		curTarget = target;
	}
	clock_t now = clock();
	curAimTime += static_cast<float>(now - lastAimTime) / CLOCKS_PER_SEC;
	lastAimTime = now;
	float percent = min(curAimTime / Settings::Aimbot::smoothingAmount, 1.0);

	Vec3 targetAngle = CalcAngle(localPlayerPtr->pos, target->pos);
	targetAngle.x += 90;
	vec3 currentAngle = { localPlayerPtr->yaw,localPlayerPtr->pitch,0 };
	if (Settings::Aimbot::smoothing) {
		if (percent >= 1) {
			curAimTime = 0;
			percent = 1;
		}
		smoothAngel(currentAngle, targetAngle, percent);
		std::cout << "smooth" << std::endl;
	}
	else {
		currentAngle = targetAngle;

	}
	localPlayerPtr->yaw = currentAngle.x;
	localPlayerPtr->pitch = currentAngle.y;
}