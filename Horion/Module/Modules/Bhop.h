#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bhop : public IModule {
public:
	float speed = 0.50f;
	bool hive = false;
	int timer = 20;
	int speedIndexThingyForHive = 20;
	float epicHiveSpeedArrayThingy[21] = {
		0.450888,
		0.432595,
		0.420948,
		0.410800,
		0.397015,
		0.384470,
		0.373055,
		0.362666,
		0.353213,
		0.344611,
		0.336783,
		0.329659,
		0.323177,
		0.317277,
		0.311909,
		0.307024,
		0.302579,
		0.298534,
		0.294852,
		0.291502,
		0.265267};
	C_MoveInputHandler* yes;
	C_MoveInputHandler cachedInput;
	Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
		registerBoolSetting("Hive", &hive, hive);
		registerFloatSetting("Speed", &speed, speed, 0.10f, 1.50f);
		registerIntSetting("Timer", &timer, timer, 20, 50);
	}
	~Bhop(){};
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Bhop"); }
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onTick(C_GameMode* gm) override {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
	}
	//virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override { g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f); }
	virtual void onEnable() override { speedIndexThingyForHive = 20; }
};