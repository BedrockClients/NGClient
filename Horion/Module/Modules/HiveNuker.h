#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class HiveNuker : public IModule {
private:
	int range = 5;
	bool destroy;
	vec3_ti blockPos;

public:
	HiveNuker();
	~HiveNuker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* packet) override;
};