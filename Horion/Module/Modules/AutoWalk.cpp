#include "AutoWalk.h"
#include "../ModuleManager.h"

AutoWalk::AutoWalk() : IModule(0, Category::MOVEMENT, "Automatically walk for you") {
	this->registerBoolSetting("Sprint", &this->sprint, this->sprint);
	this->registerBoolSetting("Jump", &this->jump, this->jump);
}

AutoWalk::~AutoWalk() {}

const char* AutoWalk::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (sprint && jump) {
			return "AutoClick [Both]";
		} else if (jump) {
			return "AutoClick [Jump]";
		} else if (sprint) {
			return "AutoClick [Sprint]";
		}
	} else
		return "AutoClick";
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