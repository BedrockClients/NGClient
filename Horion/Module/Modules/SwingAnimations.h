#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class SwingAnimations : public IModule {
public:
	bool floppySwing = false;
	bool fluxSwing = true;
	bool noObstructSwing = false;
	bool pushSwing = false;
	bool fakeJavaSwing = false;
	void* targetAddress;
	void* targetAddress2;
	SettingEnum enum1;

	SwingAnimations();
	~SwingAnimations();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};