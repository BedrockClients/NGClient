#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Partner : public IModule {
public:
	SettingEnum Partnered;
	Partner();
	~Partner();

		// Inherited via IModule
	virtual const char* getModuleName() override;
};