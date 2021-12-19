#include "Teams.h"

Teams::Teams() : IModule(0, Category::COMBAT, "DOSENT WORK!!!") {
	registerBoolSetting("is allied", &alliedCheck, alliedCheck);
	registerBoolSetting("same color", &colorCheck, colorCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
