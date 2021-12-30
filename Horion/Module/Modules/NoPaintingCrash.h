#pragma once
#include "Module.h"
class NoPaintingCrash : public IModule {
public:
	NoPaintingCrash() : IModule(0, Category::WORLD, "Fix Painting crash when using mob spawner !") {}
	~NoPaintingCrash(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("NoPaintingCrash"); }
};