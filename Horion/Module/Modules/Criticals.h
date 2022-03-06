#pragma once
#include "Module.h"
class Criticals : public IModule {
public:
	Criticals() : IModule(0, Category::COMBAT, "Each hit is a critical hit") {}
	~Criticals(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Criticals"); }
	virtual void onSendPacket(C_Packet* packet) override {
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->onGround = false;
		}
	}
};