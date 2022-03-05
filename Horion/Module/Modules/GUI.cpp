#include "GUI.h"
#include "../ModuleManager.h"

float GUI::rcolor{0.f};
float GUI::gcolor{0.f};
float GUI::bcolor{0.f};

GUI::GUI() : IModule(0, Category::GUI, "ArrayList") {
	//
	registerBoolSetting("Flux Bar", &Fluxbar, Fluxbar);
	registerBoolSetting("under Bar", &underbar, underbar);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("Icy", &ice, ice);
	registerBoolSetting("Bottom Right", &bottom, bottom);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Keybinds", &keybinds, keybinds);
	registerSpace("");
	registerBoolSetting("Badman Arraylist", &badman, badman);
	registerBoolSetting("Surge Arraylist", &Surge, Surge);
	registerBoolSetting("Horion Arraylist", &Horion, Horion);
	registerBoolSetting("Weather Arraylist", &weather, weather);
	registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
	//

}

GUI::~GUI() {
}

const char* GUI::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (badman) {
			return "Arraylist [Badman]";
		} else if (bar || bottom) {
			return "Arraylist [Bar]";
		} else if (rgb) {
			return "Arraylist [RGB]";
		} else if (ice) {
			return "Arraylist [Icy]";
		} else if (bottom) {
			return "Arraylist [Bottom]";
		} else return "Arraylist";
	} else
		return "Arraylist";
}