#pragma once
#include "Module.h"

class MineplexFly : public IModule {
private:
	int delay = 0;
	bool isBypass = false;
	bool up = false;
	float speedMod = 0.70f;
	float yUp = 0.5f;
	float glideMod = -0.00f;
	float glideModEffective = 0.f;
	float upanddown = 0.6f;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	MineplexFly();
	~MineplexFly();

	virtual void onTick(C_GameMode* gm) override;
	virtual bool isFlashMode() override;
	virtual void onDisable() override;
	virtual void onEnable() override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
#pragma once
