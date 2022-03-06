#include "Miner.h"

Miner::Miner() : IModule(0x0, Category::WORLD, "Excavates blocks around you") {
	registerBoolSetting("Show Range", &radius, radius);
	registerIntSetting("Red", &customR, customR, 0, 255);
	registerIntSetting("Green", &customG, customG, 0, 255);
	registerIntSetting("Blue", &customB, customB, 0, 255);
	registerBoolSetting("Dont Mine Ores", &ores, ores);
	registerIntSetting("Range", &range, range, 1, 10);
	registerIntSetting("Height +", &up, up, 1, 10);
	registerIntSetting("Height -", &down, down, 1, 10);
}

Miner::~Miner() {
}

const char* Miner::getModuleName() {
	return ("Miner");
}

void Miner::onTick(C_GameMode* gm) {
	if (!ores) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					gm->destroyBlock(&blockPos, 1);
				}
			}
		}
	} else {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					bool destroy = true;
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

					if (id == 7 || id == 56 || id == 129 || id == 14 || id == 73 || id == 74 || id == 21 || id == 15 || id == 16 || id == 526 || id == 536 || id == 153 || id == 543 && ores) destroy = false;

					if (destroy) {
						gm->destroyBlock(&blockPos, 1);
					}
				}
			}
		}
	}
}

void Miner::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (radius) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_t blockPos = vec3_t(x, y, z);

					C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
					C_BlockLegacy* blockLegacy = (block->blockLegacy);
					bool render = true;

					if (render) {
						static auto Minermod = moduleMgr->getModule<Miner>();
						DrawUtils::setColor(((float)Minermod->customR / (float)255), ((float)Minermod->customG / (float)255), ((float)Minermod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15)));
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), 0.4f);
					}
				}
			}
		}
	}
}