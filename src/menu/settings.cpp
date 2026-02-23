#include "settings.h"  
#include "imgui/imgui.h"

namespace Settings {
namespace ESP {
	 bool enabled;
	 bool drawTeam;
	ImColor* enemyColor=new ImColor(0,0,255,255);
	ImColor* mateColor = new ImColor(255, 0, 0, 255);

}

namespace Aimbot {
	bool enabled;

}
}