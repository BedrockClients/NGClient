#pragma once
#include "Module.h"

class AntiLagBack : public IModule {
public:
	AntiLagBack();
	~AntiLagBack();

	const char* getModuleName() override;
};