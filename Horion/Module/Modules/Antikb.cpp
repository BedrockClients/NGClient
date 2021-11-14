#include "Antikb.h"

Antikb::Antikb() : IModule(0, Category::MOVEMENT, "No knockback") {
	registerFloatSetting("Linear Modifier", &xMod, xMod, 0.f, 1.f);
	registerFloatSetting("Height Modifier", &yMod, yMod, 0.f, 1.f);
}

Antikb::~Antikb() {
}

const char* Antikb::getModuleName() {
	return ("Anti knockback");
}

void Antikb::onTick(C_GameMode* gm) {
}