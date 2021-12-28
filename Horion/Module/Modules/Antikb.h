#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Antikb : public IModule {
public:
	float xMod = 0.f;
	float yMod = 0.f;
	Antikb() : IModule(0x0, Category::MOVEMENT, "No knockback"){
		registerFloatSetting("Linear Modifier", &xMod, xMod, 0.f, 1.f);
		registerFloatSetting("Height Modifier", &yMod, yMod, 0.f, 1.f);
};
	~Antikb(){};

	virtual const char* getModuleName() override {
		return "AntiKnockback";
	}
};