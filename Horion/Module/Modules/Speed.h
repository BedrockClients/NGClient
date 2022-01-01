#pragma once
#include "Module.h"

class Speed : public IModule {
private:
	float origSpeed = 0;
	float speed = 1.6f;

public:
	Speed() : IModule(VK_NUMPAD2, Category::MOVEMENT, "Speed up!") {
		registerFloatSetting("speed", &speed, 1, 0.1f, 3.f);
	}
	~Speed(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Speed"); }
	virtual void onTick(C_GameMode* gm) override {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = speed;
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr) {
			setEnabled(false);
			return;
		} else {
			origSpeed = *reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		}
	}
	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() != nullptr)
			*reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84) = origSpeed;
	}
};