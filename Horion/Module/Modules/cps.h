#pragma once
#include "Module.h"

class cps : public IModule {
public:
	cps();
	~cps();

	float scale = 1.f;
	float cpsX = 110.f;
	float cpsY = 310.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};