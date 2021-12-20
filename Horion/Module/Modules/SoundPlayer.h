#pragma once
#include "Module.h"
class SoundPlayer : public IModule {
private:
	bool random = false;
	int sound = 0;

public:
	SoundPlayer();
	~SoundPlayer();
	// Inherited via IModule
	virtual void onSendPacket(C_Packet* packet);
	virtual const char* getModuleName() override;
};
