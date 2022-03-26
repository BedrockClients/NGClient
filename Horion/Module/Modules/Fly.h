#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Fly : public IModule {
public:
	float speed = 1.5f;
	int gameTick = 0;
	float glideModEffective = -0;
	float glideMod = -.0f;
	SettingEnum mode;

	Fly() : IModule(0x0, Category::FLYS, "become birb") {
		registerFloatSetting("Speed", &speed, speed, 0.1f, 3.f);
		registerEnumSetting("Mode", &mode, 0);
		mode = (*new SettingEnum(this))
				   .addEntry(EnumEntry("Fly", 1))
				   .addEntry(EnumEntry("CubeFly", 2))
				   .addEntry(EnumEntry("Vanilla", 3))
				   .addEntry(EnumEntry("CubeGlide", 4))
				   .addEntry(EnumEntry("Mineplex", 5));
	};
	~Fly(){};

	bool isFlashMode() {
		switch (mode.selected) {
		case 0:
			return false;
			break;
		case 1:
			return true;
			break;
		}
		return false;
	}

	void onEnable() {
		if (mode.selected == 1) {
			g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(vec3_t(0, 1, 0)));
		}
	}

	void onTick(C_GameMode* gm) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (input == nullptr) return;
		if (GameData::isKeyDown(*input->sneakKey) && (mode.selected == 2))
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);

		if (mode.selected == 3)
			gm->player->canFly = true;

		if (mode.selected == 1) {
			gameTick++;

			vec3_t pos = *g_Data.getLocalPlayer()->getPos();
			pos.y += 1.3f;
			C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y -= 1.3f;
			C_MovePlayerPacket a2(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.z = sin(calcYaw) * speed;

			gm->player->lerpMotion(moveVec);

			if (gameTick >= 5) {
				gameTick = 0;
				float yaw = gm->player->yaw * (PI / 180);
				float length = 4.f;

				float x = -sin(yaw) * length;
				float z = cos(yaw) * length;

				// gm->player->setPos(pos.add(vec3_t(x, 0.5f, z)));
			}
		}
		if (mode.selected == 5) {  // by Kow
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.y = -0.0f;
			moveVec.z = sin(calcYaw) * speed;

			gm->player->lerpMotion(moveVec);
		}
		if (mode.selected == 4) {
			if (g_Data.canUseMoveKeys()) {
				if (GameData::isKeyDown(*input->spaceBarKey))
					glideModEffective += speed;
				if (GameData::isKeyDown(*input->sneakKey))
					glideModEffective -= speed;
			}
			float yaw = gm->player->yaw;
			if (input->forwardKey && input->backKey && input->rightKey && input->leftKey)
				gm->player->velocity = vec3_t(0, 0, 0);
			gm->player->velocity.y = glideModEffective;
			glideModEffective = glideMod;
		}
		if (mode.selected == 2) {
			gameTick++;

			vec3_t pos = *g_Data.getLocalPlayer()->getPos();
			pos.y += 1.3f;
			C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y -= 1.3f;
			C_MovePlayerPacket a2(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.z = sin(calcYaw) * speed;

			gm->player->lerpMotion(moveVec);

			if (gameTick >= 5) {
				gameTick = 0;
				float yaw = gm->player->yaw * (PI / 180);
				float length = 4.f;

				float x = -sin(yaw) * length;
				float z = cos(yaw) * length;

				gm->player->setPos(pos.add(vec3_t(x, 0.5f, z)));
			}
		}
	}
	void onDisable() {
		switch (mode.selected) {
		case 0:
			if (g_Data.getLocalPlayer() != nullptr)
				if (g_Data.getLocalPlayer()->gamemode != 1)
					g_Data.getLocalPlayer()->canFly = false;
			break;
		case 1:
			g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
			break;
		case 2:
			g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
		}
	}

	void onMove(C_MoveInputHandler* input) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		if (mode.selected == 2) {
			if (player == nullptr) return;
			bool pressed = moveVec2d.magnitude() > 0.01f;

			float calcYaw = (player->yaw + 90) * (PI / 180);
			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed) player->lerpMotion(moveVec);
		}
	}

	virtual const char* getModuleName() override {
		return "Fly";
	}
};