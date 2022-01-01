#include "MinevilleFly.h"
#include "../ModuleManager.h"

MinevilleFly::MinevilleFly() : IModule(0, Category::SERVER, "MinevilleFly") {
	glideMod = 0.00f;
	registerFloatSetting("Speed", &speed, speed, 1.f, 4.f);
}

MinevilleFly::~MinevilleFly() {
}

const char* MinevilleFly::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		static char modName[30];  // This is kinda ghetto rn, there should be a better way to make this...
		sprintf_s(modName, 30, "MinevilleFly [Speed: %.2f]", speed);
		return modName;
	} else
		return ("MinevilleFly");
}

void MinevilleFly::onTick(C_GameMode* gm) {
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.0f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.0f;
	}
	gm->player->velocity.y = glideModEffective;
}

const char* MinevilleFly::getRawModuleName() {
	return "MinevilleFly";
}

void MinevilleFly::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	//if (player->onGround && pressed)
	//player->jumpFromGround();

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