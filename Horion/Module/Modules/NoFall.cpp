#include "NoFall.h"

NoFall::NoFall() : IModule(0x0, Category::MOVEMENT, "NoFall") {
	registerBoolSetting("OnGround", &groundy, groundy);
	registerBoolSetting("Server", &server, server);
	registerBoolSetting("NoPacket", &nopackety, nopackety);
	registerBoolSetting("Motion", &motion, motion);
}

NoFall::~NoFall() {
}

const char* NoFall::getModuleName() {
	return ("NoFall");
}

void NoFall::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (groundy) {
		gm->player->onGround = true;
	}
	if (motion) {
		if (player->fallDistance > 4) {
			glideModEffective = glideMod;
			gm->player->velocity.y = glideModEffective;
			g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(0, 0.25, 0));  //sets how much u need
		}
	}
	if (counter == 5)
		counter = 0;
	else
		counter++;

	vec3_t blockBelow2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow2.y -= g_Data.getLocalPlayer()->height;
	blockBelow2.y -= 1.5f;
}

void NoFall::onDisable() {
}