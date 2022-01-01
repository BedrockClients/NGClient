#include "Nuker.h"
#include "../ModuleManager.h"

Nuker::Nuker() : IModule(VK_NUMPAD5, Category::WORLD, "Break multiple blocks at once") {
	registerIntSetting("radius", &nukerRadius, nukerRadius, 1, 50);
	registerBoolSetting("veinminer", &veinMiner, veinMiner);
	registerBoolSetting("auto destroy", &autodestroy, autodestroy);
}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (autodestroy) {
			return "Nuker [Auto]";
		} else if (veinMiner) {
			return "Nuker [Veins]";
		} else
			return "Nuker";
	} else
		return "Nuker";
}

void Nuker::onWorldTick(C_GameMode* gm) {
	if (!autodestroy) return;
	vec3_ti tempPos = *gm->player->getPos();
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)gm->player->getPos()->x + x;
				tempPos.y = (int)gm->player->getPos()->y + y;
				tempPos.z = (int)gm->player->getPos()->z + z;
				if (tempPos.y > -64 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
					gm->destroyBlock(&tempPos, 1);
				}
			}
		}
	}
}
