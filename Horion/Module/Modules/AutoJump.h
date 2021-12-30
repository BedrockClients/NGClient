#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AutoJump : public IModule {
public:

	AutoJump() : IModule(0x0, Category::MOVEMENT, "Automatically jump"){

	};
	~AutoJump(){};

	void onTick(C_GameMode* gm) {
		auto player = g_Data.getLocalPlayer();

		if (player->onGround) gm->player->jumpFromGround();
	}

	virtual const char* getModuleName() override {
		return "AutoJump";
	}
};