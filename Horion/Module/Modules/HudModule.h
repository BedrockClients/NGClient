#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();

	bool Msg = false;
	bool enabled = true;
	bool different = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool rgb = false;
	bool bottom = false;
	bool bools = false;
	bool rgbtext = true;
	bool tabgui = false;
	bool arraylist = true;
	bool clickToggle = true;
	bool watermark = false;
	bool coordinates = false;
	bool keybinds = true;
	bool displayArmor = true;
	bool keystrokes = true;
	bool fps = true;
	bool cps = true;
	bool alwaysShow = false;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float arrayListOpacity = 0.0f;
	float scale = 0.75f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
