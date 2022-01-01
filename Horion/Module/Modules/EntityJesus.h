#pragma once
#include "Module.h"
class EntityJesus : public IModule {
private:
	bool walk = true;
	bool wasInWater = false;

public:
	EntityJesus();
	~EntityJesus();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};