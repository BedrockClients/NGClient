#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bhop : public IModule {
public:
	float speed = 0.50f;
	float height = 1.f;
	bool hive = false;
	int timer = 20;
	int speedIndexThingyForHive = 20;
	bool ZoomHop = false;
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
		registerFloatSetting("Height", &height, height, 0.01f, 2.00f);
		registerBoolSetting("ZoomHop", &ZoomHop, ZoomHop);
		registerIntSetting("Timer", &timer, timer, 20, 50);
	}
	~Bhop(){};
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Bhop"); }
	virtual void onMove(C_MoveInputHandler* input) override {
		cachedInput = *input;
		yes = input;
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (pressed) {
			player->setSprinting(true);
			if (player->onGround) {
				player->jumpFromGround();	
				if (ZoomHop) {
					player->velocity.y = 0.368f;
				}
			}
				
		}

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		if (ZoomHop && player->onGround)
			moveVec.y = player->velocity.y;
		else if(player->onGround)
			moveVec.y = player->velocity.y * height;
		moveVec.z = moveVec2d.y * speed;

		if (pressed && hive) {
			if (ZoomHop) {
				if (player->onGround) speedIndexThingyForHive = 0;
				float currentSpeed = epicHiveSpeedArrayThingy[speedIndexThingyForHive];
				moveVec.x = moveVec2d.x * currentSpeed;
				moveVec.z = moveVec2d.y * currentSpeed;
				moveVec.y = player->velocity.y;
				player->lerpMotion(moveVec);
				if (speedIndexThingyForHive < 20) speedIndexThingyForHive++;
			} else {
				if (player->onGround) player->lerpMotion(moveVec);
			}
		} else if (pressed && !hive)
			player->lerpMotion(moveVec);
	}
	virtual void onTick(C_GameMode* gm) override {
		if (ZoomHop)
			hive = true;
		g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
	}
	//virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override { g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f); }
	virtual void onEnable() override { speedIndexThingyForHive = 20; }
};