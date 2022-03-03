#pragma once
#include "Module.h"

class ClickGuiMod : public IModule {
public:
	SettingEnum type;
	ClickGuiMod();
	~ClickGuiMod();

	static float rcolor;
	static float gcolor;
	static float bcolor;
	bool showTooltips = true;
	bool RGB = false;
	float opacity = 0.20f;

	// Inherited via IModule
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};
