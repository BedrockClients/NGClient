#pragma once
#include "Module.h"

class PacketMultiplier : public IModule {
public:
	int multiplier = 1;

	PacketMultiplier();
	~PacketMultiplier();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};