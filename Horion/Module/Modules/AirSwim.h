#pragma once
#include "Module.h"

class AirSwim : public IModule {
public:
	bool particles = true;
	AirSwim();
	~AirSwim();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};