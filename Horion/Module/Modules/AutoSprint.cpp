#include "AutoSprint.h"
#include "../ModuleManager.h"

AutoSprint::AutoSprint() : IModule(0, Category::MOVEMENT, "Automatically sprint without holding the key") {
	registerBoolSetting("all directions", &this->alldirections, this->alldirections);
}

AutoSprint::~AutoSprint() {
}

const char* AutoSprint::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (alldirections) {
			return "AutoSprint [All]";
		}
	} else
		return "AutoSprint";
}

void AutoSprint::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (!GameData::isKeyDown(*input->sneakKey)) {
		if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f) {
			if (alldirections || GameData::isKeyDown(*input->forwardKey))
				gm->player->setSprinting(true);
		}
	}
}
