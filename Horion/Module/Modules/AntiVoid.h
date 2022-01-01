#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class AntiVoid : public IModule {
private:
	vec3_t orgipos;

public:
	bool jump = false;
	int distance = 5;
	C_MoveInputHandler* inputHandler = nullptr;
	SettingEnum mode;
	AntiVoid();
	~AntiVoid();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
};