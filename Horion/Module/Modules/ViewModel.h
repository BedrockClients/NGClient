#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class ViewModel : public IModule {
public:
	int delay = 0;
	bool Reset = false;
	bool doTranslate = true;
	bool doScale = true;

	float float1 = 0;
	float xMod = 1.f;
	float yMod = 1.f;
	float zMod = 1.f;

	float xTrans = 0.f;
	float yTrans = 0.f;
	float zTrans = 0.f;

	ViewModel() : IModule(0x0, Category::VISUAL, "Custom item view model") {
		registerBoolSetting("Reset", &Reset, Reset);
		registerBoolSetting("Translate", &doTranslate, doTranslate);
		registerBoolSetting("Scale", &doScale, doScale);

		registerFloatSetting("TranslateX", &xTrans, 0.f, -2.f, 2.f);
		registerFloatSetting("TranslateY", &yTrans, 0.f, -2.f, 2.f);
		registerFloatSetting("TranslateZ", &zTrans, 0.f, -2.f, 2.f);

		registerFloatSetting("ScaleX", &xMod, 1.f, -2.f, 2.f);
		registerFloatSetting("ScaleY", &yMod, 1.f, -2.f, 2.f);
		registerFloatSetting("ScaleZ", &zMod, 1.f, -2.f, 2.f);
	};
	~ViewModel(){};

	void ViewModel::onTick(C_GameMode* gm) {
		if (g_Data.getLocalPlayer() == nullptr)
			return;

		if (Reset) {
			xTrans = 0.f;
			yTrans = 0.f;
			zTrans = 0.f;

			xMod = 1.f;
			yMod = 1.f;
			zMod = 1.f;
			Reset = false;
		}
	}


	virtual const char* getModuleName() override {
		return "ViewModel";
	}
};