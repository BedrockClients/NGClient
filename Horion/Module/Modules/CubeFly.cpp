#include "CubeFly.h"
int oldY;
CubeFly::CubeFly() : IModule('N', Category::SERVER, "Fly on CubeCraft!") {

}

CubeFly::~CubeFly() {
}

const char* CubeFly::getModuleName() {
	return "CubehoFly";
}

bool CubeFly::isFlashMode() {
	return true;
}

void CubeFly::onEnable() {
	oldY = g_Data.getLocalPlayer()->getPos()->y;
}

void CubeFly::onTick(C_GameMode* gm) {
	if (gm->player->getPos()->y <= oldY) {
		gm->player->jumpFromGround();
	}
	gm->player->onGround = true;
}

void CubeFly::onDisable() {
}
