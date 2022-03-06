#pragma once
#include "Module.h"

class bps : public IModule {
public:
	bps();
	~bps();

	float scale = 1.f;
	float bpsX = 110.f;
	float bpsY = 305.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};