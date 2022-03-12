#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Velocity : public IModule {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;

	Velocity() : IModule(0x0, Category::MOVEMENT, "Replaces Sounds") {
		registerFloatSetting("Linear Modifier", &xModifier, xModifier, 0.f, 1.f);
		registerFloatSetting("Height Modifier", &yModifier, yModifier, 0.f, 1.f);
};
	~Velocity(){};

	virtual const char* getModuleName() override {
		return "Velocity";
	}
};