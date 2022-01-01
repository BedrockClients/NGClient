#pragma once
#include "Module.h"
class Jesus : public IModule {
private:
	bool walk = false;
	bool wasInWater = false;

public:
	Jesus();
	~Jesus();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
};
