#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0, Category::SERVER, "Unknown, Android, iOS, macOS, FireOS, GearVR, HoloLens, Windows 10(PC), Windows, Dedicated, Orbis, NX") {
	registerIntSetting("Edition", &edition, edition, 0, 10);
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	return edition;
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}
