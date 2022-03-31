#pragma once
#include "Module.h"
class Blink : public IModule {
private:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;

public:
	Blink() : IModule(0x0, Category::PLAYER, "Stops you from sending packets and then sends them in a bunch") {}
	~Blink() {
		getMovePlayerPacketHolder()->clear();
		getPlayerAuthInputPacketHolder()->clear();
	}

	// Inherited via IModule
	virtual void onTick(C_GameMode* gm) override { gm->player->fallDistance = 0.f; }
	virtual const char* getModuleName() override { return ("Blink"); }

	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};