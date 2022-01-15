#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "Break any block instantly") {
	registerEnumSetting("Mode", &mode, 0);
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Normal", 0))
			   .addEntry(EnumEntry("Hold", 1))
				.addEntry(EnumEntry("FastBreak", 2));
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}
void InstaBreak::onTick(C_GameMode* gm) {
	if (GameData::isLeftClickDown() && g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->canOpenContainerScreen() && mode.selected == 1) {
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		bool isDestroyed = false;
		gm->stopDestroyBlock(pointing->block);
		gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
		gm->destroyBlock(new vec3_ti(pointing->block), pointing->blockSide);
		gm->stopDestroyBlock(pointing->block);
	}
}