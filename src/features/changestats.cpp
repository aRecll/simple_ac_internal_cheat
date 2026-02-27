#include "changestats.h"
#include <iostream>
void updateStats()
{
	if (Settings::Stats::infinityAmmo) {
		if (localPlayerPtr->rifleAmmo < 100 and Settings::Stats::infinityRiffleAmmo) localPlayerPtr->rifleAmmo = 200;
		if (localPlayerPtr->shotgunAmmo < 100 and Settings::Stats::infinityShotgunAmmo) localPlayerPtr->shotgunAmmo = 200;
		if (localPlayerPtr->smgAmmo < 100 and Settings::Stats::infinitySmgAmmo) localPlayerPtr->smgAmmo = 200;
		if (localPlayerPtr->pistolAmmo < 100 and Settings::Stats::infinityPistolAmmo) localPlayerPtr->pistolAmmo = 200;


	}
	if (Settings::Stats::infinityHealt) {
		if (localPlayerPtr->health < 100) {
			localPlayerPtr->health = 1000;
		}
	}

}
void updateFOV()
{
	if (Settings::Stats::customFov != *pFOV) {
		*pFOV = Settings::Stats::customFov;

	}
}

void updateSpeedOfShuts()
{
	if (Settings::Aimbot::rapidFire) {
		localPlayerPtr->shotgunDelay = 1;
		localPlayerPtr->rifleDelay = 1;
		localPlayerPtr->sniperDelay = 1;
	}
	
	
}

