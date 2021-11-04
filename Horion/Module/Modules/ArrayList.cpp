#include "ArrayList.h"

#include "../ModuleManager.h"

float ArrayList::rcolor{0.f};
float ArrayList::gcolor{0.f};
float ArrayList::bcolor{0.f};

ArrayList::ArrayList() : IModule(0, Category::GUI, "ArrayList") {
	this->registerBoolSetting("Icy Arraylist", &this->ice, this->ice);
	this->registerBoolSetting("RGB", &this->rgb, this->rgb);
	//this->registerBoolSetting("RGB text", &this->rgbtext, this->rgbtext);
	this->registerBoolSetting("Surge Client Colors", &this->different, this->different);
	this->registerBoolSetting("Side Bar", &this->bar, this->bar);
	this->registerBoolSetting("Bottom Bar", &this->underbar, this->underbar);
	this->registerBoolSetting("Bottom Right", &this->bottom, this->bottom);
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
