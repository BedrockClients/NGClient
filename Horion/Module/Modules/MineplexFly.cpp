#include "MineplexFly.h"
#include "../ModuleManager.h"

MineplexFly::MineplexFly() : IModule('R', Category::SERVER, "Flight bypass for Mineplex") {
	registerFloatSetting("speed", &speedMod, 1, 0.3f, 2.5f);
	registerFloatSetting("Y-Start", &yUp, 1, 0.0f, 1.f);
    registerBoolSetting("Up", &isBypass, isBypass);
	registerBoolSetting("Up+", &up, up);
}

MineplexFly::~MineplexFly() {
}

bool MineplexFly::isFlashMode() {
	return true;
}

void MineplexFly::onDisable() {
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos((pos, pos, pos));
	g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}

void MineplexFly::onEnable() {
	vec3_t moveVec;
	float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
	float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);
	float teleportX = cos(calcYaw) * cos(calcPitch) * -0.0f;
	float teleportZ = sin(calcYaw) * cos(calcPitch) * -0.0f;
	moveVec.y = +yUp;
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y + yUp, pos.z + teleportZ));
}

const char* MineplexFly::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (up) {
			return "MineplexFly [Up+]";
		} else if (isBypass) {
			return "MineplexFly [Up]";
		} else
			return "MineplesFly";
	} else
		return "MineplexFly";
}

void MineplexFly::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);

	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = -0.0f * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	} else {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = +0.007f * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	}
}