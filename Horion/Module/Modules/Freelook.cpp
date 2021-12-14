#include "Freelook.h"

#include "../../../Utils/Logger.h"

Freelook::Freelook() : IModule(0, Category::VISUAL, "Move straight while moving your camera around") {
}
Freelook::~Freelook() {
}
const char* Freelook::getModuleName() {
	return "Freelook";
}

void Freelook::onEnable() {
	oldPos = g_Data.getLocalPlayer()->viewAngles;
}
void Freelook::onDisable() {
	g_Data.getLocalPlayer()->applyTurnDelta(&oldPos);
}
void Freelook::onTick(C_GameMode* gm) {
	
}