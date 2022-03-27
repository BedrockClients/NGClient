#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Notifications : public IModule {
public:
	Notifications() : IModule(0x0, Category::GUI, "Shows Enabled/Disabled Modules In Chat!"){
	};
	~Notifications(){};

	virtual const char* getModuleName() override { 
	return "Notifications"; 
	}
};
