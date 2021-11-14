#include "AutoClick.h"

AutoClick::AutoClick() : IModule(0, Category::COMBAT, "A simple AutoClick, automatically clicks for you.") {
	registerBoolSetting("rightclick", &rightclick, rightclick);
	registerBoolSetting("only weapons", &weapons, weapons);
	registerBoolSetting("break blocks", &breakBlocks, breakBlocks);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hold", &hold, hold);
}

AutoClick::~AutoClick() {
}

const char* AutoClick::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (breakBlocks) {
			return "AutoClick [Break]";
		} else if (rightclick) {
			return "AutoClick [Attack]";
		} else if (weapons) {
			return "AutoClick [Weapons]";
		} else if (hold) {
			return "AutoClick [Hold]";
		}
	} else
		return "AutoClick";
}

void AutoClick::onTick(C_GameMode* gm) {
	if ((GameData::isLeftClickDown() || !hold)) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		Odelay++;

		if (Odelay >= delay) {
			auto selectedItem = localPlayer->getSelectedItem();
			if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
				return;
			if (!rightclick) {
				if (pointing->hasEntity()) {
					g_Data.leftclickCount++;
					localPlayer->swingArm();
					gm->attack(pointing->getEntity());
				} else if (breakBlocks) {
					bool isDestroyed = false;
					localPlayer->swingArm();
					g_Data.leftclickCount++;
					gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
					if (isDestroyed && localPlayer->region->getBlock(pointing->block)->blockLegacy->blockId != 0)
					gm->destroyBlock(&pointing->block, pointing->blockSide);
					if (isDestroyed) 
						gm->stopDestroyBlock(pointing->block);
				}
				Odelay = 0;
			}
		}
	}

	if (rightclick) {
		if ((GameData::isRightClickDown() || !hold) && g_Data.isInGame()) {
			PointingStruct* pstruct = g_Data.getClientInstance()->getPointerStruct();
			Odelay++;
			if (Odelay >= delay) {
				g_Data.rightclickCount++;
				C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
				localPlayer->swingArm();
				gm->startBuildBlock(vec3_ti(pstruct->block), pstruct->blockSide);
				gm->stopBuildBlock();
				gm->buildBlock(new vec3_ti(pstruct->block), pstruct->blockSide);
				Odelay = 0;
			}
		}
	}
}