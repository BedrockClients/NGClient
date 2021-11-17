#include "HiveNuker.h"

HiveNuker::HiveNuker() : IModule(VK_NUMPAD9, Category::SERVER, "Destroys blocks around you") {
	registerIntSetting("Range", &
		
		
		
		range, this->range, 1, 8);
}

HiveNuker::~HiveNuker() {
}

const char* HiveNuker::getModuleName() {
	return ("HiveNuker");
}

void HiveNuker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (gm->player->region->getBlock(blockPos)->toLegacy()->blockId) destroy = true;

				if (destroy) {
					bool isDestroyed = false;
					gm->startDestroyBlock(blockPos, 0, isDestroyed);
					gm->destroyBlock(&blockPos, 0);
					gm->stopDestroyBlock(blockPos);
					g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}
}