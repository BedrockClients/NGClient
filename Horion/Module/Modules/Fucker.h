#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Fucker : public IModule {
private:
	int range = 5;
	bool beds = false;
	bool eggs = false;
	bool cakes = false;
	bool treasures = false;
	bool chests = true;
	bool redstone = false;
	bool diamond = false;
	bool emerald = false;
	bool bypass = false;

public:
	Fucker();
	~Fucker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
};