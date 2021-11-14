#include "Speed.h"
Speed::Speed() : IModule(VK_NUMPAD2, Category::MOVEMENT, "Speed up!") {
	registerFloatSetting("speed", &this->speed, 1, 0.1f, 3.f);
}
Speed::~Speed() {
}
const char* Speed::getModuleName() {
	return ("Speed");
}
void Speed::onTick(C_GameMode* gm) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	// intop THIS IS HOW U GET THE ACTUAL SPEED NUMBER!!!
	float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
	*speedAdr = speed;
}

void Speed::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	} else {
		origSpeed = *reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
	}
}
void Speed::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		*reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84) = origSpeed;
}