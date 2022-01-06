#pragma once
#include "../../DrawUtils.h"
#include "Module.h"
class Nuker : public IModule {
public:
	int delay = 0;
	int nukerRadius = 50;
	bool veinMiner = false;
	bool autodestroy = true;
	Nuker() : IModule(0, Category::WORLD, "Break multiple blocks at once") {
	registerIntSetting("radius", &nukerRadius, nukerRadius, 1, 50);
	registerBoolSetting("veinminer", &veinMiner, veinMiner);
	registerBoolSetting("auto destroy", &autodestroy, autodestroy);
	}
	~Nuker(){};

	void onTick(C_GameMode* gm) {
		if (!autodestroy) return;
		vec3_ti tempPos = *gm->player->getPos();
		for (int x = -nukerRadius; x < nukerRadius; x++) {
			for (int y = -nukerRadius; y < nukerRadius; y++) {
				for (int z = -nukerRadius; z < nukerRadius; z++) {
					tempPos.x = (int)gm->player->getPos()->x + x;
					tempPos.y = (int)gm->player->getPos()->y + y;
					tempPos.z = (int)gm->player->getPos()->z + z;
					if (tempPos.y > -68 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
						gm->destroyBlock(&tempPos, 1);
					}
				}
			}
		}
	}

		virtual const char* getModuleName() override {
		return "Nuker";
	}
};