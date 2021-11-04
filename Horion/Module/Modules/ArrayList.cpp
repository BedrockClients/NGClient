#include "ArrayList.h"

#include "../ModuleManager.h"

float ArrayList::rcolor{0.f};
float ArrayList::gcolor{0.f};
float ArrayList::bcolor{0.f};

ArrayList::ArrayList() : IModule(0, Category::GUI, "ArrayList") {
	registerBoolSetting("Icy Arraylist", &ice, ice);
	registerBoolSetting("RGB", &rgb, rgb);
	//registerBoolSetting("RGB text", &rgbtext, rgbtext);
	registerBoolSetting("Surge Client Colors", &different, different);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("Bottom Bar", &underbar, underbar);
	registerBoolSetting("Bottom Right", &bottom, bottom);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
	registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);
}

ArrayList::~ArrayList() {
}

const char* ArrayList::getModuleName() {
	return "ArrayList";
}
