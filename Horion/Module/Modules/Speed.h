#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class Speed : public IModule {
public:
	float origSpeed = 0;
	float speed = 1.6f;
	bool hive = false;
	C_MoveInputHandler* yes;
	C_MoveInputHandler cachedInput;
	SettingEnum speedMode;

	Speed() : IModule(VK_NUMPAD2, Category::MOVEMENT, "Speed up!") {
		registerFloatSetting("speed", &speed, 1, 0.1f, 3.f);
		registerEnumSetting("Mode", &speedMode, 0);
		speedMode = (*new SettingEnum(this))
			.addEntry(EnumEntry("Strafe", 0))
			.addEntry(EnumEntry("HiveOld", 1))
			.addEntry(EnumEntry("Ability", 2))
			.addEntry(EnumEntry("HiveGround", 3))
			.addEntry(EnumEntry("Teleport", 4));
	}
	~Speed(){};

	virtual const char* getModuleName() override { return ("Speed"); }

	int speedIndexThingyForHive = 30;

	float epicHiveSpeedArrayThingy[31] = {
		0.980000,
		0.575560,
		0.555560,
		0.544032,
		0.517356,
		0.503081,
		0.480991,
		0.460888,
		0.442595,
		0.425948,
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
		0.265267,
		0.241393,
		0.219668,
		0.199898
	};

	virtual void onTick(C_GameMode* gm) override {
		if (speedMode.selected == 2) {//Ability
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
			*speedAdr = speed;
		}
	}
	virtual void onEnable() override {
		speedIndexThingyForHive = 30;
		if (g_Data.getLocalPlayer() == nullptr) {
			setEnabled(false);
			return;
		} else {
			if (speedMode.selected == 2)  // Ability
				origSpeed = *reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		}
	}
	virtual void onMove(C_MoveInputHandler* input) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr) return;
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;
		float calcYaw = (player->yaw + 90) * (PI / 180);

		if (speedMode.selected == 0) {//Strafe
			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed)
				player->lerpMotion(moveVec);
		}

		if (speedMode.selected == 1) {  //Hive
			cachedInput = *input;
			yes = input;

			if (pressed) {
				player->setSprinting(true);
				if (player->onGround)
					player->jumpFromGround();
				C_MovePlayerPacket mpp(player, *player->getPos());
				mpp.onGround = player->onGround;
				mpp.pitch += 0.5f;
				mpp.yaw += 0.5f;
				mpp.headYaw += 0.5f;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
			}

			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};

			if (pressed) {
				if (player->onGround) speedIndexThingyForHive = 0;
				float currentSpeed = epicHiveSpeedArrayThingy[speedIndexThingyForHive];
				moveVec.x = moveVec2d.x * currentSpeed;
				moveVec.z = moveVec2d.y * currentSpeed;
				if (player->onGround) moveVec.y = 0.08f;
				else moveVec.y = player->velocity.y;
				player->lerpMotion(moveVec);
				if (speedIndexThingyForHive < 30) speedIndexThingyForHive++;
			}
		}

		if (speedMode.selected == 3) {  // HiveGround
			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed)
				player->lerpMotion(moveVec);
			if (pressed && player->onGround) {
				if (g_Data.getLocalPlayer()->velocity.squaredxzlen() > 0.01) {
					C_MovePlayerPacket p2 = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(player->velocity.x / 1.3f, 0.f, player->velocity.z / 2.3f)));
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p2);
					//Made by Founder, don't take or skid you nigger monkey
				}
			}
		}

		if (speedMode.selected == 4 && pressed) { // Teleport
			auto pos = *g_Data.getLocalPlayer()->getPos();
			float length = speed;
			vec3_t moveVec;

			float x = cos(calcYaw) * length;
			float z = sin(calcYaw) * length;

			player->setPos(pos.add(vec3_t(x, 0.f, z)));
		}
	}

	virtual void onSendPacket(C_Packet* packet) override {
		//static auto SF = moduleMgr->getModule<Scaffold>();
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (speedMode.selected == 3 /* && ((!SF->isEnabled() && SF->SukinMyBigJuicyAss) || (SF->isEnabled() && !SF->SukinMyBigJuicyAss))*/) {
			if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && g_Data.isInGame()) {
				auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				float myPitchq = player->pitch;
				float myYawq = player->yaw;
				float bodyYawq = player->bodyYaw;

				C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

				if (input == nullptr)
					return;

				float yaw = player->yaw;

				if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
					return;
				else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
					yaw += 45.f;
				} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
					yaw -= 45.f;
				} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
					yaw += 135.f;
				} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
					yaw -= 135.f;
				} else if (GameData::isKeyDown(*input->forwardKey)) {
				} else if (GameData::isKeyDown(*input->backKey)) {
					yaw += 180.f;
				} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
					yaw += 90.f;
				} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
					yaw -= 90.f;
				}
				if (yaw >= 180)
					yaw -= 360.f;
				float calcYaw = (yaw + 90) * (PI / 180);

				movePacket->headYaw = yaw;
			}
		}
	}

	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() != nullptr && speedMode.selected == 2)
			*reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84) = origSpeed;
	}
};