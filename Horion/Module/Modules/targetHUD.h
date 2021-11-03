#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class targetHUD : public IModule {
public:
	bool targetHUDlist = true;
	float targetHUDopacity = true;

	targetHUD();
	~targetHUD();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* ctx) override;
};