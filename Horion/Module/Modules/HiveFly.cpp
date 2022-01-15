#include "HiveFly.h"
int counter = 0;
bool clip = false;
float clipHeight = 2.f;
HiveFly::HiveFly() : IModule('0', Category::SERVER, "How the fuck does this bypass ?!?!?") {
	registerBoolSetting("Clip Up", &clip, clip);
	registerFloatSetting("Clip Height", &clipHeight, clipHeight, 0.5f, 5.f);
}

HiveFly::~HiveFly() {
}

const char* HiveFly::getModuleName() {
	return ("HiveFly");
}

float epicHiveFlySpeedArrayThingy[15] = {
	0.810000,
	0.615560,
	0.583347,
	0.554032,
	0.527356,
	0.503081,
	0.480991,
	0.460888,
	0.442595,
	0.425948,
	0.410800,
	0.397015,
	0.384470,
	0.373055,
	0.362666
};

int flySpeedIndex = 0;

bool dontGoDown = true;

void HiveFly::onEnable() {
	srand(time(NULL));
	counter = 0;
	flySpeedIndex = 0;
	dontGoDown = true;
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (player->onGround == true && clip) {
			vec3_t myPos = *player->getPos();
			myPos.y += clipHeight;
			player->setPos(myPos);
			player->jumpFromGround();
		}
	}
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	float moveSpeed = epicHiveFlySpeedArrayThingy[flySpeedIndex++ % 15];
	moveVec.x = moveVec2d.x * moveSpeed;

	if (dontGoDown)
		moveVec.y = 0.f;
	else
		moveVec.y = player->velocity.y;
	dontGoDown = !dontGoDown;

	moveVec.z = moveVec2d.y * moveSpeed;
	if (pressed) player->lerpMotion(moveVec);
	if (!pressed) {
		player->velocity.x = 0;
		player->velocity.z = 0;
	}
}

void HiveFly::onSendPacket(C_Packet* packet) {
}

void HiveFly::onLevelRender() {
}

void HiveFly::onDisable() {
	counter = 0;
	if (g_Data.getLocalPlayer() != nullptr) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->velocity.y = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}