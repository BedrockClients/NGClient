#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class FullBright : public IModule {
public:
	float intensity = 25.f;
	float* gammaPtr = nullptr;

	FullBright() : IModule(0x0, Category::VISUAL, "Puts your gamma to max") {
		registerFloatSetting("Intensity", &intensity, intensity, -25.f, 25.f);
	};
	~FullBright(){};

	float originalGamma = -1;

	void onWorldTick(C_GameMode* gm) {
		if (gammaPtr != nullptr && *gammaPtr != 10)
			*gammaPtr = 10;
	}

	void onEnable() {
		if (gammaPtr != nullptr) {
			originalGamma = *gammaPtr;
			*gammaPtr = 10;
		}
	}

	void onDisable() {
		if (gammaPtr != nullptr) {
			if (originalGamma >= 0 && originalGamma <= 1)
				*gammaPtr = originalGamma;
			else
				*gammaPtr = 0.5f;
		}
	}

	virtual const char* getModuleName() override {
		return "FullBright";
	}
};