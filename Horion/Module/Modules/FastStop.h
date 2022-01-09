#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class FastStop : public IModule {
public:
	FastStop() : IModule(0x0, Category::PLAYER, "Stop faster"){
	};
	~FastStop(){};

	virtual const char* getModuleName() override {
		return "FastStop";
	}
	virtual void onMove(C_MoveInputHandler* input) {
		auto player = g_Data.getLocalPlayer();
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;
		if (!pressed)
			if (player->onGround) {
				player->velocity.x = 0;
				player->velocity.z = 0;
			}
	}
};
