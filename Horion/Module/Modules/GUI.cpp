#include "GUI.h"
#include "../ModuleManager.h"

float GUI::rcolor{0.f};
float GUI::gcolor{0.f};
float GUI::bcolor{0.f};

GUI::GUI() : IModule(0, Category::GUI, "ArrayList") {

	//registerBoolSetting("Box", &box, box);
	registerBoolSetting("Better RGB Colors", &different, different);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("under Bar", &underbar, underbar);
	registerBoolSetting("Icy", &ice, ice);
	registerBoolSetting("Bottom Right", &bottom, bottom);
	//registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
	registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);

}

GUI::~GUI() {
}

const char* GUI::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (different) {
			return "Arraylist [BetterRBG]";
		} else if (bar || bottom) {
			return "Arraylist [Bar]";
		} else if (rgb) {
			return "Arraylist [RGB]";
		} else if (ice) {
			return "Arraylist [Icy]";
		} else if (bottom) {
			return "Arraylist [Bottom]";
		}
	} else
		return "Arraylist";
}