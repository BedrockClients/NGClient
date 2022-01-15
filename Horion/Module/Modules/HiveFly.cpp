#include "HiveFly.h"
int counter = 0;
bool clip = false;
float clipHeight = 2.f;
int counter69 = 0;
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
	0.450888,
	0.432595,
	0.420948,
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
	0.311909
};

int flySpeedIndex = 0;

bool dontGoDown = true;

void HiveFly::onEnable() {
	srand(time(NULL));
	counter = 0;
	counter69 = 0;
	flySpeedIndex = 0;
	dontGoDown = true;
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (player->onGround == true) {
			if (clip) {
				vec3_t myPos = *player->getPos();
				myPos.y += clipHeight;
				player->setPos(myPos);
			} else {
				counter69++;
				if (counter69 <= 2) {
					player->jumpFromGround();
				}
			}
		} else {
			counter69 = 6;
		}
	}
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	counter69++;
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

		if (counter69 >= 6 && !clip) {
			if (pressed) player->lerpMotion(moveVec);

		} else if (clip) {
			if (pressed) player->lerpMotion(moveVec);
		}

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
	counter69 = 0;
	counter = 0;
	if (g_Data.getLocalPlayer() != nullptr) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->velocity.y = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}