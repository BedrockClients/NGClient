#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();
	bool Buttons = false;
	bool Msg = true;
	bool notifications = false;
	bool Hud = true;
	bool enabled = true;
	bool rgb = false;
	bool bools = false;
	bool rgbtext = true;
	bool displaySecondHalf = true;
	bool tabgui = false;
	bool arraylist = true;
	bool surge = false;
	bool watermark = false;
	bool keybinds = true;
	bool keybindsRGB = true;
	bool displayArmor = false;
	bool keystrokes = true;
	bool alwaysShow = false;
	bool bottom = false;
	float opacity = true;
	float scale = 0.75f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
