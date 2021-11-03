#include "GUI.h"

float GUI::rcolor{0.f};
float GUI::gcolor{0.f};
float GUI::bcolor{0.f};

GUI::GUI() : IModule(0, Category::GUI, "ArrayList") {

	//registerBoolSetting("Box", &box, box);
	registerBoolSetting("Surge colors", &different, different);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("RGB Borders", &rgb, rgb);
	registerBoolSetting("under Bar", &underbar, underbar);
	registerBoolSetting("Icey", &ice, ice);
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
	return ("Arraylist");
}