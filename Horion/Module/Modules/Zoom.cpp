#include "Zoom.h"
#include "../ModuleManager.h"

Zoom::Zoom() : IModule('C', Category::VISUAL, "Zoom in or out!") {
	registerFloatSetting("Strength", &this->strength, this->strength, -100.f, 100.f);
	registerBoolSetting("Smooth", &this->smooth, this->smooth);
}

Zoom::~Zoom() {
}

bool Zoom::isFlashMode() {
	return true;
}

const char* Zoom::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (smooth) 
			return "Zoom [Smooth]";
		else
			return "Zoom";
	} else
		return "Zoom";
}

void Zoom::onEnable() {
	zooming = true;
}

void Zoom::onDisable() {
	target = g_Data.fov;
}
