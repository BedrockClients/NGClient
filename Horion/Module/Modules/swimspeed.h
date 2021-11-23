#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class swim : public IModule {
private:
float speed = 0.325f;
	
public:
	swim();
	~swim();

	virtual const char* getModuleName() override;
	void onTick(C_GameMode* gm);
	virtual void onDisable() override;
};