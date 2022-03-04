#pragma once
#include "Module.h"

class GUI : public IModule {

public:

	GUI();
	~GUI();
	//
	SettingEnum ArrayList;
	//
	bool rgb = true;//NG RGB
	bool badman = false;//Badman RGB
	bool Surge = false;//Surge RGB
	bool Horion = false;//Horion RGB
	bool weather = false;//weather RGB
	//
	bool box = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool Fluxbar = false;
	bool bottom = false;
	bool rgbtext = true;
	bool clickToggle = true;
	bool keybinds = true;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};