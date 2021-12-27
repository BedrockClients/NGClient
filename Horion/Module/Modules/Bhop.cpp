#include "Bhop.h"

Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerBoolSetting("Timer", &timer, timer);
	registerBoolSetting("LowHop", &LowHop, LowHop);
	registerBoolSetting("Hive", &hive, hive);
	registerBoolSetting("Rotations", &rot, rot);
	registerBoolSetting("Speed", &bhopspeed, bhopspeed);
	registerFloatSetting("LowHop Frequency", &hight, hight, 0.1f, 1.f);
	registerFloatSetting("Bhop Speed", &speed, speed, 0.1f, 1.0f);
	registerFloatSetting("Timer Speed", &tspeed, tspeed, 0.21f, 2.f);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (timer) {
			return "Bhop [Timer]";
		} else if (LowHop) {
			return "Bhop [Low]";
		} else if (hive) {
			return "Bhop [Hive]";
		} else if (bhopspeed) {
			return "Bhop [Speed]";
		} else
			return "Bhop";
	} else
		return "Bhop";
}

void Bhop::onMove(C_MoveInputHandler* input) {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (player->onGround && pressed)
		player->jumpFromGround();

	if (counter == 1) {
		if (pressed && LowHop) {
			player->velocity.y -= hight;
		}
	}

	if (counter == 2) {
		counter = 0;
	} else {
		counter++;
	}

	if (pressed && bhopspeed) {
		player->velocity.y = -0.5f;
	}
	if (player->onGround && hive) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	} else if (!hive) {
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

void Bhop::onTick(C_GameMode* gm) {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	if (timer) {
		*g_Data.getClientInstance()->minecraft->timer = 72.f * tspeed;
	}
	if (rot) {
		auto player = g_Data.getLocalPlayer();
		player->yaw = player->bodyYaw - 180;
		player->yaw = player->bodyYaw + 180;
		player->yaw = player->bodyYaw + 360;
		player->pitch = player->yaw;
	}
}

void Bhop::onDisable() {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}