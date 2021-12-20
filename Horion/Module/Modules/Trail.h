#pragma once
#include "Module.h"
class Trail : public IModule {
public:
	Trail();
	~Trail();

	std::vector<vec3_t> linePoints;
	std::vector<vec3_t> linePoints1;
	std::vector<vec3_t> linePoints2;
	std::vector<vec3_t> linePoints3;
	std::vector<vec3_t> linePoints4;
	std::vector<vec3_t> linePoints5;

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
