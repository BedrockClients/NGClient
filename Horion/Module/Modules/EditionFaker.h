#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class EditionFaker : public IModule {
private:
	int edition = 0;

public:
	EditionFaker() : IModule(0x0, Category::SERVER, "Unknown" /*, Android, iOS, macOS, FireOS, GearVR, HoloLens, Windows 10(PC), Windows, Dedicated, Orbis, NX */) {
		registerIntSetting("Edition", &edition, edition, 1, 13);
		/* 
		1 Android
		2 IOS
		3
		4 Kindle Fire
		5
		6
		7 Wondows
		8
		9
		10 PC
		11 PS4
		12 Switch
		13 XBOX*/
		
	};
	~EditionFaker(){};

	int EditionFaker::getFakedEditon() {
		return edition;
	}

	virtual const char* getModuleName() override {
		return "EditionFaker";
	}
};