#pragma once
#include "Module.h"

class Freecam : public IModule {
private:
	vec3_t oldPos;
	float speed = 0.325f;
	float vspeed = 0.3f;

public:
	Freecam();
	~Freecam();

	vec3_t targetPos;
	vec2_t cameraRot = {0.f, 0.f};
	vec2_t lastPos;
	bool wasDisabled = false;
	bool freezerot = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext*) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender()override;
};