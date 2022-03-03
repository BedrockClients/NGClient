#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAura : public IModule {
public:
	int range = 7;
	int delay = 0;
	bool doMultiple = true;
	vec3_t espPosUpper;
	vec3_t espPosLower;


	CrystalAura();
	~CrystalAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};