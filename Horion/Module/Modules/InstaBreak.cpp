#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "Break any block instantly") {
	registerBoolSetting("Hold", &bypass, bypass);
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}
void InstaBreak::onTick(C_GameMode* gm) {
	if (GameData::isLeftClickDown() && g_Data.isInGame() && g_Data.canUseMoveKeys() && bypass && g_Data.getLocalPlayer()->canOpenContainerScreen()) {
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		bool isDestroyed = false;
		gm->stopDestroyBlock(pointing->block);
		gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
		gm->destroyBlock(new vec3_ti(pointing->block), pointing->blockSide);
	}
}
