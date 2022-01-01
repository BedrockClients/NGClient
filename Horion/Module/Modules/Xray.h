#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Xray : public IModule {
public:
	bool* smoothLightningSetting = nullptr;
	bool gotSmoothInfo = false;
	bool wasSmooth = false;

	Xray() : IModule(0x0, Category::VISUAL, "Allows you to see certain blocks easier"){};
	~Xray(){};

	void onTick(C_GameMode* gm) {
		if (smoothLightningSetting != nullptr) {
			if (!gotSmoothInfo) {
				gotSmoothInfo = true;
				wasSmooth = *smoothLightningSetting;
			}
			*smoothLightningSetting = 0;
		}
	}

	void onDisable() {
		if (smoothLightningSetting != nullptr && gotSmoothInfo) {
			*smoothLightningSetting = wasSmooth;
		}
		gotSmoothInfo = false;
	}

	virtual const char* getModuleName() override {
		return "Xray";
	}
};