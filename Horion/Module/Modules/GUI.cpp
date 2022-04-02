#include "GUI.h"

#include "../ModuleManager.h"

float GUI::rcolor{0.f};
float GUI::gcolor{0.f};
float GUI::bcolor{0.f};

GUI::GUI() : IModule(0x0, Category::GUI, "ArrayList") {
	registerBoolSetting("Arraylist RGB", &rgb, rgb);
	registerBoolSetting("Flux Bar", &Fluxbar, Fluxbar);
	registerBoolSetting("under Bar", &underbar, underbar);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("Icy", &ice, ice);
	registerBoolSetting("Bottom Right", &bottom, bottom);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Keybinds", &keybinds, keybinds);

	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry(EnumEntry("Badman RGB", 0));
	mode.addEntry(EnumEntry("Surge", 1));
	mode.addEntry(EnumEntry("Horion", 2));
	mode.addEntry(EnumEntry("Surge V2", 3));
	mode.addEntry(EnumEntry("Fadeaway", 4));
	mode.addEntry(EnumEntry("NG", 5));
	mode.addEntry(EnumEntry("Weather", 6));
	mode.addEntry(EnumEntry("Cool RGB", 7));
	mode.addEntry(EnumEntry("Badman", 8));
	
	registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
}

GUI::~GUI() {
}

const char* GUI::getModuleName() {
		return "Arraylist";
}