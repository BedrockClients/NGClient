#pragma once
#include "Module.h"
class Surround : public IModule {
public:
	SettingEnum enum1;
	bool renderSurround = true;
	bool disableOnComplete2 = true;
	bool doReset = true;
	std::vector<vec3_t> surrArr;

	std::vector<vec3_t> regularBlocks = {
		vec3_t(0, -1, 0),
		vec3_t(1, -1, 0),
		vec3_t(1, 0, 0),
		vec3_t(0, -1, 1),
		vec3_t(0, 0, 1),
		vec3_t(-1, -1, 0),
		vec3_t(-1, 0, 0),
		vec3_t(0, -1, -1),
		vec3_t(0, 0, -1),
	};
	std::vector<vec3_t> antiCityBlocks = {
		vec3_t(0, -1, 0),
		vec3_t(1, -1, 0),
		vec3_t(1, 0, 0),
		vec3_t(2, 0, 0),
		vec3_t(0, -1, 1),
		vec3_t(0, 0, 1),
		vec3_t(0, 0, 2),
		vec3_t(-1, -1, 0),
		vec3_t(-1, 0, 0),
		vec3_t(-2, 0, 0),
		vec3_t(0, -1, -1),
		vec3_t(0, 0, -1),
		vec3_t(0, 0, -2),
	};

	Surround();
	~Surround();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};