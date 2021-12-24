#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();

	bool Msg = true;
	bool Hud = true;
	bool enabled = true;
	bool different = false;
	bool rgb = true;
	bool bools = false;
	bool rgbtext = true;
	bool tabgui = false;
	bool arraylist = true;
	bool clickToggle = true;
	bool watermark = false;
	bool coordinates = true;
	bool keybinds = true;
	bool displayArmor = false;
	bool keystrokes = true;
	bool fps = true;
	bool cps = true;
	bool alwaysShow = false;
	float opacity = true;
	bool bottom = false;
	float scale = 0.75f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
