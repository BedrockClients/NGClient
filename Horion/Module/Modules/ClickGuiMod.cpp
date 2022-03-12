#include "ClickGuiMod.h"

#include "../../Menu/ClickGui.h"

// Backgrund color
float ClickGuiMod::rcolor{0.f};
float ClickGuiMod::gcolor{0.f};
float ClickGuiMod::bcolor{0.f};

// Module On color
float ClickGuiMod::trcolor{0.f};
float ClickGuiMod::tgcolor{1.f};
float ClickGuiMod::tbcolor{1.f};

// Module Off color
float ClickGuiMod::tfrcolor{1.f};
float ClickGuiMod::tfgcolor{1.f};
float ClickGuiMod::tfbcolor{1.f};

ClickGuiMod::ClickGuiMod() : IModule(VK_TAB, Category::GUI, "The clickgui") {
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips);
	registerIntSetting("Font", &font, font, 1, 9);
	registerBoolSetting("RGB", &RGB, RGB);
	registerSpace("Enabled Colors");
	registerFloatSetting("Module On Red", &trcolor, trcolor, 0.f, 1.f);
	registerFloatSetting("Module On Green", &tgcolor, tgcolor, 0.f, 1.f);
	registerFloatSetting("Module On Blue", &tbcolor, tbcolor, 0.f, 1.f);
	registerSpace("Disabled Colors");
	registerFloatSetting("Module Off Red", &tfrcolor, tfrcolor, 0.f, 1.f);
	registerFloatSetting("Module Off Green", &tfgcolor, tfgcolor, 0.f, 1.f);
	registerFloatSetting("Module Off Blue", &tfbcolor, tfbcolor, 0.f, 1.f);
	registerSpace("Background Colors");
	registerFloatSetting("Backgrund Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Backgrund Green", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Backgrund Blue", &bcolor, bcolor, 0.f, 1.f);
	registerFloatSetting("Backgrund Opacity", &opacity, opacity, 0.f, 1.f);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (RGB) {
			return "ClickGui [RGB]";
		} else if (showTooltips) {
			return "ClickGui [Tooltips]";
		} else
			return "ClickGui";
	} else
		return "ClickGui";
}

void ClickGuiMod::onEnable() {
	g_Data.getClientInstance()->releaseMouse();
}

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
}

void ClickGuiMod::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys())
		g_Data.getClientInstance()->releaseMouse();
}
void ClickGuiMod::onLoadConfig(void* conf) {
	IModule::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
}
void ClickGuiMod::onSaveConfig(void* conf) {
	IModule::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
}