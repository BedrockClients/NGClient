#pragma once
#include "Module.h"
class ArmourHud : public IModule {
public:
	ArmourHud();
	~ArmourHud();

	float armorX = 327.f;
	float armorY = 282.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};