#include "aimbot.h"

#include "../utils/support.h"
#include "../utils/computingfunc.h"
void aim::aimbot()
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