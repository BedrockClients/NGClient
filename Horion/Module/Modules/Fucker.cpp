#include "Fucker.h"

Fucker::Fucker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys specific things around you") {
	registerBoolSetting("Hive Bypass", &bypass, bypass);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
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

void Fucker::onWorldTick(C_GameMode* gm) {
	if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->localPlayer->isAlive()) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					blockPos = vec3_ti(x, y, z);
					destroy = false;
					bool eat = false;
					std::string name = gm->player->region->getBlock(blockPos)->toLegacy()->name.getText();

					if (name == "bed" && beds) destroy = true;                                      // Beds
					if (name == "dragon_egg" && eggs) destroy = true;                                    // Dragon Eggs
					if (name == "cake" && cakes) eat = true;                                         // Cakes
					if (name == "chest" && chests) destroy = true;                                        // Chests
					if (name == "lit_redstone_ore" && redstone && gm->player->getAbsorption() < 10) destroy = true;  // Lit Redstone
					if (name == "redstone_ore" && redstone && gm->player->getAbsorption() < 10) destroy = true;   // Redstone
					if (name == "diamond_ore" && diamond) destroy = true;                                       // Diamond
					if (name == "emerald_ore" && emerald) destroy = true;                                        // Emerald

					if (destroy) {
						if (!bypass)
							gm->destroyBlock(&blockPos, 0);
						else {
							bool isDestroyed = false;
							gm->stopDestroyBlock(blockPos);
							gm->startDestroyBlock(blockPos, 0, isDestroyed);
							gm->destroyBlock(&blockPos, 0);
							gm->stopDestroyBlock(blockPos);
						}
					}
					if (eat) {
						gm->buildBlock(&blockPos, 0);
						if (!noSwing)
							g_Data.getLocalPlayer()->swingArm();
						return;
					}
				}
			}
		}
	}
}
void Fucker::onSendPacket(C_Packet* packet) {
}

void Fucker::onLevelRender() {
	if (treasures) {
		if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->localPlayer->isAlive()) {
			g_Data.forEachEntity([](C_Entity* ent, bool b) {
				std::string name = ent->getNameTag()->getText();
				int id = ent->getEntityTypeId();
				if (name.find("Treasure") != std::string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
					g_Data.getCGameMode()->attack(ent);
					auto breakMod = moduleMgr->getModule<Fucker>();
					if (!breakMod->noSwing)
					g_Data.getLocalPlayer()->swingArm();
				}
			});
		}
	}
}