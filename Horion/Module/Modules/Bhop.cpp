#include "Bhop.h"
float speed = 0.50f;
float height = 1.f;
bool hive = false;
int timer = 20;
Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerBoolSetting("Hive", &hive, hive);
	registerFloatSetting("Speed", &speed, speed, 0.10f, 1.00f);
	registerFloatSetting("Height", &height, height, 0.01f, 2.00f);
	registerIntSetting("Timer", &timer, timer, 20, 50);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return ("Bhop");
}

void Bhop::onEnable() {
}

void Bhop::onTick(C_GameMode* gm) {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
}

void Bhop::onMove(C_MoveInputHandler* input) {
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

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speed;
	moveVec.y = player->velocity.y * height;
	moveVec.z = moveVec2d.y * speed;

	if (pressed && hive && player->onGround) player->lerpMotion(moveVec);
	else if (pressed && !hive) player->lerpMotion(moveVec);
}

void Bhop::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
}