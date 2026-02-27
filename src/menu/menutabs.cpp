#include "menutabs.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"
#include "../offsets/constants.h"
void aimbotTab() {
    if (!ImGui::BeginTabItem("Aimbot"))
        return;
    ImGui::Checkbox("Aimbot", &Settings::Aimbot::enabled);
    ImGui::SameLine();

    ImGui::Checkbox("Rapid fire", &Settings::Aimbot::rapidFire);
    ImGui::Checkbox("Smoothing", &Settings::Aimbot::smoothing);
    if (Settings::Aimbot::smoothing) {
        ImGui::SameLine(100);
        ImGui::SetNextItemWidth(300);
        ImGui::SliderFloat("Smoothing Amount", &Settings::Aimbot::smoothingAmount, 0.1f, 1.0f);
    }


    ImGui::Checkbox("Check In Fov", &Settings::Aimbot::checkInFov);
    if (Settings::Aimbot::checkInFov) {

        ImGui::Indent(16.0f);
        ImGui::SliderFloat("Fov", &Settings::Aimbot::fov, 90.0f, 500.0f);


        ImGui::Checkbox("Draw Fov Circle", &Settings::Aimbot::drawFovCircle);
        ImGui::Unindent(16.0f);
    }

    ImGui::EndTabItem();
}
void espTab() {
    if (!ImGui::BeginTabItem("esp"))
        return;

    ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
    ImGui::Checkbox("drawTeam", &Settings::ESP::drawTeam);
    ImGui::ColorEdit4("TeamColor", (float*)&Settings::ESP::mateColor->Value);
    ImGui::ColorEdit4("enemyColor", (float*)&Settings::ESP::enemyColor->Value);
    ImGui::EndTabItem();
}


void statsTab()
{   
    if (!ImGui::BeginTabItem("Attributes"))
        return;
    ImGui::SliderFloat("FOV", &Settings::Stats::customFov, 75, 150);
    
    ImGui::Checkbox("Infiniti ammo", &Settings::Stats::infinityAmmo);
    if (Settings::Stats::infinityAmmo) {
        ImGui::Indent(16.0f);
        ImGui::Checkbox("Riffle", &Settings::Stats::infinityRiffleAmmo);
        ImGui::Checkbox("Shotgun", &Settings::Stats::infinityShotgunAmmo);

        ImGui::Checkbox("Smg", &Settings::Stats::infinitySmgAmmo);
        ImGui::Checkbox("Sniper riffle", &Settings::Stats::infinitySniperAmmo);
        ImGui::Unindent(16.0f);



    }
    ImGui::Checkbox("Infiniti health", &Settings::Stats::infinityHealt);


    ImGui::EndTabItem();


}

void testTab() {
    if (!ImGui::BeginTabItem("Testing"))
        return;
    ImGui::Text("he");



    ImGui::EndTabItem();
}
