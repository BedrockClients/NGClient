#pragma once
#include "Module.h"
class NoSlowDown : public IModule {
private:
	void* targetAddress;
	void* targetAddress2;

public:
	NoSlowDown();
	~NoSlowDown();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
