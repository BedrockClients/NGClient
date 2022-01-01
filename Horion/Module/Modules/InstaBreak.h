#pragma once
#include "Module.h"

class InstaBreak : public IModule {
public:
	bool bypass = false;
	InstaBreak();
	~InstaBreak();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
};
