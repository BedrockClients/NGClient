#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "Break any block instantly") {
	registerBoolSetting("Hive Bypass", &bypass, bypass);
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}
void InstaBreak::onTick(C_GameMode* gm) {
	if (GameData::isLeftClickDown() && bypass) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		bool isDestroyed = false;
		gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
		gm->destroyBlock(new vec3_ti(pointing->block), pointing->blockSide);
	}
}
