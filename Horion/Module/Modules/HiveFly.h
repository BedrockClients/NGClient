#pragma once
#include "Module.h"
class HiveFly : public IModule {
private:
public:
	float timer = 20.f;
	float speed = 1.f;
	HiveFly();
	~HiveFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};