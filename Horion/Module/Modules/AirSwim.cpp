#include "AirSwim.h"

AirSwim::AirSwim() : IModule(0, Category::MOVEMENT, "Swim even though your in air") {
	registerBoolSetting("Particles", &particles, particles);
}

AirSwim::~AirSwim() {
}

const char* AirSwim::getModuleName() {
	return ("AirSwim");
}

void AirSwim::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr)
		return;
	player->didEnterWaterBool = true;
	player->startSwimming();
}

void AirSwim::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->didEnterWaterBool = true;
	if (particles)
		player->doWaterSplashEffect();
	player->startSwimming();
}

void AirSwim::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr)
		return;
	player->didEnterWaterBool = false;
	player->stopSwimming();
}