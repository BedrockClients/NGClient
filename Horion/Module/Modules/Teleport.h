#pragma once
#include "Module.h"
class Teleport : public IModule {
public:
	bool hasClicked = false;
	bool onlyHand = false;
	bool bypass = false;
	bool shouldTP = false;
	vec3_t tpPos;

public:
	Teleport();
	~Teleport();

	// Inherited via IModule
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
