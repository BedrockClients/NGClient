#pragma once
#include "Module.h"
class HiveFly : public IModule {
private:
public:
	int slot;
	float timer = 20.f;
	float speed = 1.f;
	bool findBlock();
	HiveFly();
	~HiveFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender();
	virtual void onSendPacket(C_Packet* packet);
};