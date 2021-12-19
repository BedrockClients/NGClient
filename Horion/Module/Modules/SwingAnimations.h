#pragma once
#include "Module.h"
class SwingAnimations : public IModule {
private:
	void* eightbitddress;

	void* floppyAddress;
	void* floppyAddress2;

	void* fluxAddress;

	void* noObstructAddress;

	void* pushAddress;
	void* pushAddress2;

	SettingEnum setting;
public:
	SwingAnimations();
	~SwingAnimations();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
