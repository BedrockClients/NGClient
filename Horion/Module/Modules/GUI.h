#pragma once
#include "Module.h"

class GUI : public IModule {

public:

	GUI();
	~GUI();

	bool box = false;
	bool different = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool rgb = false;
	bool Fluxbar = false;
	bool bottom = false;
	bool rgbtext = true;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};