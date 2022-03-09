#pragma once
#include "Module.h"

class Coordinates : public IModule {
public:
	Coordinates();
	~Coordinates();

	float scale = 1.f;
	float CoordinatesX = 210.f;
	float CoordinatesY = 55.f;
	float NetherX = 210.f;
	float NetherY = 55.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};