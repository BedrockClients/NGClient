#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class EditionFaker : public IModule {
private:
	int edition = 0;

public:
	EditionFaker() : IModule(0x0, Category::SERVER, "Unknown" /*, Android, iOS, macOS, FireOS, GearVR, HoloLens, Windows 10(PC), Windows, Dedicated, Orbis, NX */) {
		registerIntSetting("Edition", &edition, edition, -1, 14);
		//not know
		//-1 11 12 13 14
	};
	~EditionFaker(){};

	int EditionFaker::getFakedEditon() {
		return edition;
	}

	virtual const char* getModuleName() override {
		return "EditionFaker";
	}
};