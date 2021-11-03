#pragma once
#include "Module.h"
class Trail : public IModule {
public:
	Trail();
	~Trail();

	std::vector<vec3_t> linePoints;
	vec3_t startPos;
	vec3_t startPosTop;

	bool clearondisable = true;
	bool stopTrail = false;
	bool Rainbow = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onDisable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
