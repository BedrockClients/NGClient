#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class FightBot : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	float reach = 4.f;
	bool hurttime = true;

public:
	float range = 6.f;
	vec2_t bot;
	FightBot();
	~FightBot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
};