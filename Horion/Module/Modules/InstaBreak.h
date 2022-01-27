#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class InstaBreak : public IModule {
public:
	SettingEnum mode;

	InstaBreak() : IModule(0x0, Category::WORLD, "Break any block instantly") {
		registerEnumSetting("Mode", &mode, 0);
		mode = SettingEnum(this)
				   .addEntry(EnumEntry("Normal", 0))
				   .addEntry(EnumEntry("Hold", 1))
				   .addEntry(EnumEntry("FastBreak", 2));
	};
	~InstaBreak(){};

	void onTick(C_GameMode* gm) {
		if (GameData::isLeftClickDown() && g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->canOpenContainerScreen() && mode.selected == 1) {
			PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
			bool isDestroyed = false;
			gm->stopDestroyBlock(pointing->block);
			gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
			vec3_ti* thingy = new vec3_ti(pointing->block);
			gm->destroyBlock(thingy, pointing->blockSide);
			gm->stopDestroyBlock(pointing->block);
			delete thingy;
		}
	}

	virtual const char* getModuleName() override {
		return "InstaBreak";
	}
};