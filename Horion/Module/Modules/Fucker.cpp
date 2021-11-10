#include "Fucker.h"

Fucker::Fucker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys specific things around you") {
	registerBoolSetting("Hive Bypass", &bypass, bypass);
	registerIntSetting("Range", &range, range, 1, 10);
	registerBoolSetting("Beds", &beds, beds);
	registerBoolSetting("Eggs", &eggs, eggs);
	registerBoolSetting("Cakes", &cakes, cakes);
	registerBoolSetting("Treasures", &treasures, treasures);
	registerBoolSetting("Chests", &chests, chests);
	registerBoolSetting("Redstone", &redstone, redstone);
	registerBoolSetting("Diamonds", &diamond, diamond);
	registerBoolSetting("Emeralds", &emerald, emerald);
}

Fucker::~Fucker() {
}

const char* Fucker::getModuleName() {
	return ("Breaker");
}

void Fucker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				bool eat = false;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 26 && beds) destroy = true;    // Beds
				if (id == 122 && eggs) destroy = true;   // Dragon Eggs
				if (id == 92 && cakes) eat = true;       // Cakes
				if (id == 54 && chests) destroy = true;  // Chests
				if (id == 73 && redstone) destroy = true;
				if (id == 74 && redstone) destroy = true;  // Redstone
				if (id == 56 && diamond) destroy = true;   // Diamond
				if (id == 129 && emerald) destroy = true;  // Emerald
				if (destroy) {
					if (!bypass)
						gm->destroyBlock(&blockPos, 0);
					else {
						bool isDestroyed = false;
						gm->startDestroyBlock(blockPos, 0, isDestroyed);
						gm->destroyBlock(&blockPos, 0);
						gm->stopDestroyBlock(blockPos);
					}
				}
				if (eat) {
					gm->buildBlock(&blockPos, 0);
					g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}
}

void Fucker::onLevelRender() {
	if (treasures) {
		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			std::string name = ent->getNameTag()->getText();
			int id = ent->getEntityTypeId();
			if (name.find("Treasure") != std::string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
				g_Data.getCGameMode()->attack(ent);
				g_Data.getLocalPlayer()->swingArm();
			}
		});
	}
}