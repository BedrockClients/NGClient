#include "Teams.h"

Teams::Teams() : IModule(0, Category::COMBAT, "DOSENT WORK!!!") {
	registerBoolSetting("is allied", &this->alliedCheck, this->alliedCheck);
	registerBoolSetting("same color", &this->colorCheck, this->colorCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
