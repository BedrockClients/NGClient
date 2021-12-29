#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Zoom : public IModule {
public:
	bool smooth = true;
	bool zooming = false;
	float strength = 20.f;
	float target = 20.f;
	float modifier = 20.f;

	Zoom() : IModule(0x0, Category::VISUAL, "Zoom in or out!") {
		registerFloatSetting("Strength", &strength, strength, -100.f, 100.f);
		registerBoolSetting("Smooth", &smooth, smooth);
	};
	~Zoom(){};

	void Zoom::onEnable() {
		zooming = true;
	}

	void Zoom::onDisable() {
		target = g_Data.fov;
	}
	virtual const char* getModuleName() override {
		return "Zoom";
	}

};