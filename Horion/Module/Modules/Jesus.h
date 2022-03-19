#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Jesus : public IModule {
public:
	bool wasInWater = false;

	Jesus() : IModule(0x0, Category::MOVEMENT, "Walk over water, like Jesus") {
	};
	~Jesus(){};

	void Jesus::onTick(C_GameMode* gm) {
		if (gm->player->isSneaking()) return;

		if (gm->player->hasEnteredWater()) {
			gm->player->velocity.y = 0.06f;
			gm->player->onGround = true;
			wasInWater = true;
		} else if (gm->player->isInWater() || gm->player->isInLava()) {
			gm->player->velocity.y = 0.1f;
			gm->player->onGround = true;
			wasInWater = true;
		} else {
			if (wasInWater) {
				wasInWater = false;
				gm->player->velocity.x *= 1.2f;
				gm->player->velocity.x *= 1.2f;
			}
		}
	}

	virtual const char* getModuleName() override {
		return "Jesus";
	}
};
