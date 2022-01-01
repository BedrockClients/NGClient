#pragma once
#include "Module.h"
class Flyto : public IModule {
private:
	float speed = 1.5f;
	int gameTick = 0;
	bool vanilla = true;
	bool cubeMode = false;
	bool mineplexMode = false;
	bool dmg = true;

public:
	Flyto();
	~Flyto();

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};