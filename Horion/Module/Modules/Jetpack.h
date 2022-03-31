#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Jetpack : public IModule {
public:
	C_MovePlayerPacket* jetpack = nullptr;
	int delay = 0;
	bool isBypass = false;
	float speedMod = 1;

	Jetpack() : IModule(0x0, Category::FLYS, "Fly around like you had a Jetpack!") {
		registerFloatSetting("speed", &speedMod, 1, 0.2f, 15.f);
		registerBoolSetting("Bypass", &isBypass, isBypass);
	};
	~Jetpack(){};
	bool isFlashMode() {
		return true;
	}

	void onTick(C_GameMode* gm) {
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);
		float calcPitch = (gm->player->pitch) * -(PI / 180);

		if (!isBypass) {
			vec3 moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.y = sin(calcPitch) * speedMod;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			gm->player->lerpMotion(moveVec);
		} else {
			delay++;

			if (delay >= 5) {
				vec3 pos = *g_Data.getLocalPlayer()->getPos();
				C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				pos.y += 0.35f;
				a = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);

				gm->player->velocity.y = 0.465f;
				vec3 moveVec;
				moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
				moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

				gm->player->velocity.x = moveVec.x;
				gm->player->velocity.z = moveVec.z;

				float teleportX = cos(calcYaw) * cos(calcPitch) * 0.00000005f;
				float teleportZ = sin(calcYaw) * cos(calcPitch) * 0.00000005f;

				pos = *gm->player->getPos();
				g_Data.getLocalPlayer()->setPos(vec3(pos.x + teleportX, pos.y - 0.15f, pos.z + teleportZ));

				gm->player->velocity.y -= 0.15f;
	
				delay = 0;
			}
		}
	}

	virtual const char* getModuleName() override {
		return "Jetpack";
	}
};
