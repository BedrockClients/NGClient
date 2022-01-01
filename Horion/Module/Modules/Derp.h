#pragma once
#include "Module.h"
class Derp : public IModule {
private:
	int counter = 0;
	bool epicStroke = false;
	bool packetMode = false;
	bool hive = false;

public:
	Derp();
	~Derp();

	// Inherited via IModule
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};