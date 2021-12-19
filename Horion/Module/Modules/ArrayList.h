#pragma once
#include "../../DrawUtils.h"
#include "Module.h"
class ArrayList : public IModule {
public:
	bool enabled = true;
	bool different = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool rgb = true;
	bool bottom = false;
	bool rgbtext = true;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float scale = 0.75f;

	ArrayList();
	~ArrayList();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};