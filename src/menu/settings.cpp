#include "settings.h"  
#include "imgui/imgui.h"

namespace Settings {
	namespace ESP {
		bool enabled=true;
		bool drawTeam=false;
		ImColor* enemyColor = new ImColor(0, 0, 255, 255);
		ImColor* mateColor = new ImColor(255, 0, 0, 255);

	}

	namespace Aimbot {
		bool enabled=true;
		
		bool smoothing=false;
		float smoothingAmount=1.0f;
		bool checkInFov=true;
		float fov = 180;
		bool drawFovCircle=false;
		bool rapidFire = 0;
	}
	namespace Stats {
		bool infinityAmmo=false;
		bool infinityPistolAmmo= true;
		bool infinityShotgunAmmo = true;

		bool infinitySmgAmmo = true;

		bool infinitySniperAmmo = true;

		bool infinityRiffleAmmo = true;
		bool infinityHealt = false;
		bool infinityArmor = false;
		float customFov = 90;
	}
}