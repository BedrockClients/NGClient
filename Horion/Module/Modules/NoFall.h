#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class NoFall : public IModule {
private:
	bool groundy = false;
	int counter = 1;
	bool hive = true;
	bool motion = false;
	float glideMod = 0.f;
	float glideModEffective = 0;

public:
	bool server = false;
	bool nopackety = false;
	float range = 3;
	NoFall();
	~NoFall();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onTick(C_GameMode* gm);
	void onDisable();
};