#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class TriggerBot : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool sword = true;

public:
	TriggerBot();
	~TriggerBot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
};
