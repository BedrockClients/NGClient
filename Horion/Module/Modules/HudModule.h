#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();

	bool Msg = true;
	bool notifications = true;
	bool Hud = true;
	bool enabled = true;
	bool different = false;
	bool rgb = false;
	bool bools = false;
	bool rgbtext = true;
	bool displaySecondHalf = true;
	bool tabgui = false;
	bool arraylist = true;
	bool surge = false;
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
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
