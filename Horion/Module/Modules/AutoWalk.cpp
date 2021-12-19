#include "AutoWalk.h"
#include "../ModuleManager.h"

AutoWalk::AutoWalk() : IModule(0, Category::MOVEMENT, "Automatically walk for you") {
	registerBoolSetting("Sprint", &sprint, sprint);
	registerBoolSetting("Jump", &jump, jump);
}

AutoWalk::~AutoWalk() {}

const char* AutoWalk::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (sprint && jump) {
			return "AutoWalk [Both]";
		} else if (jump) {
			return "AutoWalk [Jump]";
		} else if (sprint) {
			return "AutoWalk [Sprint]";
		} else
			return "AutoWalk";
	} else
		return "AutoWalk";
}

void AutoWalk::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();

	g_Data.getClientInstance()->getMoveTurnInput()->forward = true;

	if (sprint) gm->player->setSprinting(true);
	if (!sprint) gm->player->setSprinting(false);

	if (player->onGround && jump) gm->player->jumpFromGround();
}

void AutoWalk::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
}