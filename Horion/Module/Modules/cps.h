#pragma once
#include "Module.h"

class cps : public IModule {
public:
	cps();
	~cps();

	float scale = 1.f;
	float cpsX = 210.f;
	float cpsY = 45.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};