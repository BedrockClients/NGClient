#include "ClickGuiMod.h"

#include "../../Menu/ClickGui.h"

ClickGuiMod::ClickGuiMod() : IModule(VK_TAB, Category::GUI, "The clickgui") {
	//registerIntSetting("Font", &font, font, 1, 10);
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips);
	registerBoolSetting("RGB", &RGB, RGB);
	registerBoolSetting("Surge", &surge, surge);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (surge) {
			return "ClickGui [Surge]";
		} else if (RGB) {
			return "ClickGui [RGB]";
		} else if (showTooltips) {
			return "ClickGui [Tooltips]";
		}
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