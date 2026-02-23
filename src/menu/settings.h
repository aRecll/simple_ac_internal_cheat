#pragma once

class ImColor;
namespace Settings {
	namespace ESP {
		extern bool enabled;
		extern bool drawTeam;
		extern ImColor* enemyColor;
		extern ImColor* mateColor;

	}

	namespace Aimbot {
		extern bool enabled;
		extern bool smoothing;
		extern float smoothingAmount;
		extern bool checkInFov;
		extern bool drawFovCircle;
		extern float fov;


	}

}