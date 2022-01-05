#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bhop : public IModule {
public:
	C_MoveInputHandler* yes;
	Bhop();
	~Bhop();
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	void onTick(C_GameMode* gm);
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override;
	virtual void onEnable() override; 
};