#pragma once
#include "Module.h"

class EntitySpeed : public IModule {
private:
	float speed = 1.f;

public:
	EntitySpeed();
	~EntitySpeed();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
};