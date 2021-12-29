#include "Freecam.h"

#include <chrono>

Freecam::Freecam() : IModule('V', Category::VISUAL, "Move your cam without moving the player") {
	registerFloatSetting("Horizontal Speed", &speed, speed, 0.1f, 1.8f);
	registerFloatSetting("Vertical Speed", &vspeed, vspeed, 0.1f, 1.8f);
	registerBoolSetting("Freeze Rot", &freezerot, freezerot);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}

void Freecam::onPostRender(C_MinecraftUIRenderContext*) {
	static auto prevTime = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> tDiff = now - prevTime;
	prevTime = now;
	float TimeMultiplier = tDiff.count() / 0.05f;
	if (wasDisabled) {
		TimeMultiplier = 1.f;
		wasDisabled = false;
	}

	float yaw = cameraRot.y;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (GameData::isKeyDown(*input->sneakKey)) {
		targetPos.y -= speed * TimeMultiplier;
	}
	if (GameData::isKeyDown(*input->spaceBarKey)) {
		targetPos.y += speed * TimeMultiplier;
	}
	if (GameData::isKeyDown(*input->rightKey)) {
		yaw += 90.f;
		if (GameData::isKeyDown(*input->forwardKey))
			yaw -= 45.f;
		else if (GameData::isKeyDown(*input->backKey))
			yaw += 45.f;
	}
	if (GameData::isKeyDown(*input->leftKey)) {
		yaw -= 90.f;
		if (GameData::isKeyDown(*input->forwardKey))
			yaw += 45.f;
		else if (GameData::isKeyDown(*input->backKey))
			yaw -= 45.f;
	}
	if (GameData::isKeyDown(*input->backKey) && !GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey))
		yaw += 180.f;

	bool pressed = GameData::isKeyDown(*input->forwardKey) || GameData::isKeyDown(*input->backKey) || GameData::isKeyDown(*input->rightKey) || GameData::isKeyDown(*input->leftKey);
	if (pressed) {
		float calcYaw = (yaw + 90) * (PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = 0;
		moveVec.z = sin(calcYaw) * speed;
		targetPos = targetPos.add(moveVec.mul(TimeMultiplier));
	}
}
void Freecam::onLevelRender(){
	if (!g_Data.isInGame())
		setEnabled(false);
	g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
	g_Data.getClientInstance()->getMoveTurnInput()->isJumping = 0;
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = 0;
	g_Data.getLocalPlayer()->setSneaking(false);
}
void Freecam::onEnable() {
	targetPos = *g_Data.getLocalPlayer()->getPos();
	lastPos = g_Data.getLocalPlayer()->viewAngles;
	wasDisabled = true;
}

void Freecam::onDisable() {
	wasDisabled = true;
}