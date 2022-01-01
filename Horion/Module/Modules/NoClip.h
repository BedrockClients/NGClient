#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NoClip : public IModule {
public:
	vec3_t oldPos;
	float speed = 0.325f;
	float upanddown = 0.6f;
	float glideMod = -0.00f;
	float glideModEffective = 0;
	bool NoPacket = false;

	NoClip() : IModule(0x0, Category::MOVEMENT, "NoClip through walls on all axis") {
		registerFloatSetting("Horizontal Speed", &speed, speed, 0.1f, 1.f);
		registerFloatSetting("Vertical Speed", &upanddown, upanddown, 0.1f, 1.f);
		registerBoolSetting("Save Old POS", &NoPacket, NoPacket);
	};
	~NoClip(){};

	void onTick(C_GameMode* gm) {
		gm->player->aabb.upper.y = gm->player->aabb.lower.y - (float)1.8f;
		gm->player->velocity = vec3_t(0, 0, 0);
		glideModEffective = glideMod;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (g_Data.canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->spaceBarKey))
				glideModEffective += upanddown;
			if (GameData::isKeyDown(*input->sneakKey))
				glideModEffective -= upanddown;
		}
		gm->player->velocity.y = glideModEffective;
	}

	void onMove(C_MoveInputHandler* input) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		float yaw = player->yaw;

		bool pressed = input->forward || input->backward || input->right || input->left;

		if (input->forward && input->backward)
			return;

		if (input->right) {
			yaw += 90.f;
			if (input->forward)
				yaw -= 45.f;
			else if (input->backward)
				yaw += 45.f;
		}
		if (input->left) {
			yaw -= 90.f;
			if (input->forward)
				yaw += 45.f;
			else if (input->backward)
				yaw -= 45.f;
		}

		if (input->backward && !input->left && !input->right)
			yaw += 180.f;

		float calcYaw = (yaw + 90) * (PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * speed;
		if (pressed) player->lerpMotion(moveVec);
	}

	void onEnable() {
		if (g_Data.getLocalPlayer() != nullptr) {
			oldPos = *g_Data.getLocalPlayer()->getPos();
		}
	}

	void onDisable() {
		if (g_Data.getLocalPlayer() != nullptr)
			g_Data.getLocalPlayer()->aabb.upper.y = g_Data.getLocalPlayer()->aabb.lower.y + (float)1.8f;
		if (NoPacket)
			g_Data.getLocalPlayer()->setPos(oldPos);
	}

	virtual const char* getModuleName() override {
		return "NoClip";
	}
};