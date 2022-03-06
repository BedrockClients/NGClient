#pragma once
#include "Module.h"

class fps : public IModule {
public:
	fps();
	~fps();

	float scale = 1.f;
	float fpsX = 210.f;
	float fpsY = 55.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};