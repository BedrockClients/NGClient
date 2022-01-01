#pragma once

#include "Module.h"

class LongJump : public IModule {
private:
	float height = 1.f;
	bool slow = false;
	float speed = 2.f;
	bool hit = false;

public:
	LongJump();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};