#include "Bhop.h"

#include <stack>
float speed = 0.50f;
float height = 1.f;
bool hive = false;
int timer = 20;
bool ZoomHop = false;
Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerBoolSetting("Hive", &hive, hive);
	registerFloatSetting("Speed", &speed, speed, 0.10f, 1.00f);
	registerFloatSetting("Height", &height, height, 0.01f, 2.00f);
	registerBoolSetting("ZoomHop", &ZoomHop, ZoomHop);
	registerIntSetting("Timer", &timer, timer, 20, 50);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return ("Bhop");
}

void Bhop::onEnable() {
}

C_MoveInputHandler cachedInput;

void Bhop::onTick(C_GameMode* gm) {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
}

void Bhop::onSendPacket(C_Packet* packet) {
}

int lastTick = 0;

void Bhop::onMove(C_MoveInputHandler* input) {
	cachedInput = *input;
	yes = input;
	auto player = g_Data.getLocalPlayer();
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
			if (ZoomHop) {
				C_PlayerActionPacket jmp;
				jmp.entityRuntimeId = player->entityRuntimeId;
				jmp.face = 0;
				jmp.action = 8;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&jmp);
			} 
			else {
				player->jumpFromGround();
			}
		} 
		else if (player->velocity.y > -0.35f) {
			player->velocity.y -= 0.12f;
		}
		C_MovePlayerPacket mpp(player, *player->getPos());
		mpp.onGround = player->onGround;
		mpp.pitch += 0.5f;
		mpp.yaw += 0.5f;
		mpp.headYaw += 0.5f;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
	}

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speed;
	if (ZoomHop) moveVec.y = 0.3f;
	else moveVec.y = player->velocity.y * height;
	moveVec.z = moveVec2d.y * speed;

	if (pressed && hive && player->onGround) player->lerpMotion(moveVec);
	else if (pressed && !hive) player->lerpMotion(moveVec);
}

void Bhop::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
}
