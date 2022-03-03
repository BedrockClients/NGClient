#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class RainbowSky : public IModule {
public:
	RainbowSky() : IModule(0x0, Category::VISUAL, "Makes your sky look rainbow!"){};
	~RainbowSky(){};

	virtual const char* getModuleName() override {
		return "RainbowSky";
	}
};