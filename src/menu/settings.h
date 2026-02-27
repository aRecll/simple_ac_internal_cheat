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
		extern bool rapidFire;


	}
	namespace Stats {
		extern bool infinityAmmo;
		extern bool infinityPistolAmmo;
		extern bool infinityShotgunAmmo;

		extern bool infinitySmgAmmo;

		extern bool infinitySniperAmmo;

		extern bool infinityRiffleAmmo;
		extern bool infinityHealt;
		extern bool infinityArmor;
		extern float customFov;


	}

}