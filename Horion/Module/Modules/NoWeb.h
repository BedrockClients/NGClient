#pragma once
#include "Module.h"
class NoWeb : public IModule {
public:
	NoWeb() : IModule(0, Category::MOVEMENT, "Ignore cobwebs slowdown") {}
	~NoWeb(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("NoWeb"); }
	virtual void onWorldTick(C_GameMode* gm) override { gm->player->slowdownFactor = {0, 0, 0}; }
};