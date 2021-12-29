#pragma once
#include "Module.h"

class AutoPot : public IModule {
private:
	int health = 5;
	bool findPot();
	bool isPot(C_ItemStack* itemStack);

public:
	AutoPot();
	~AutoPot();

	virtual void onSendPacket(C_Packet* packet);
	virtual void onTick(C_GameMode* gm) override;
	const char* getModuleName() override;
};
