#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Miner : public IModule {
private:
	bool radius = false;
	bool ores = false;
	int customR = 1;
	int customG = 1;
	int customB = 1;
	int range = 3;
	int up = 1;
	int down = 1;

public:
	Miner();
	~Miner();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};