#pragma once
#include "Module.h"

class Freelook : public IModule {
private:
public:
	vec2_t oldPos;
	vec2_t Pos;

	Freelook();
	~Freelook();

	virtual const char* getModuleName() override;
	void onTick(C_GameMode* mode) override;
	void onEnable() override;
	void onDisable() override;
	bool callWhenDisabled() override {
		return true;
	}
};