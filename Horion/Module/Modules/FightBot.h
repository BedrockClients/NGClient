#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class FightBot : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = false;

public:
	bool rotations = false;
	bool isMulti = true;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 100;
	float reach = 6;
	bool targetListA = false;
	bool sexy = true;
	vec2_t bot;

	FightBot();
	~FightBot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onSendPacket(C_Packet* packet) override;
};