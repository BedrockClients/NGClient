#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class CubeFly : public IModule {
public:
	int oldY;

	float speed = 1.5f;
	float ystart = 1.f;
	float yflying = 0.5f;
	int gameTick = 0;
	int delaytp = 5;
	int tpdist = 3;

	CubeFly() : IModule(0x0, Category::SERVER, "Fly on CubeCraft!"){

	};
	~CubeFly(){};

	bool isFlashMode() {
		return true;
	}

	void onEnable() {
		oldY = g_Data.getLocalPlayer()->getPos()->y;
	}

	void onTick(C_GameMode* gm) {
		if (gm->player->getPos()->y <= oldY) {
			gm->player->jumpFromGround();
		}
		gm->player->onGround = true;
	}

	virtual const char* getModuleName() override {
		return "CubeFly";
	}
};