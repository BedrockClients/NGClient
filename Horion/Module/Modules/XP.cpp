#include "XP.h"

XP::XP() : IModule(0x0, Category::SERVER, "Gives You Shit Loads Of XP!") {
	registerIntSetting("amount", &amount, amount, 1, 5000);
}

XP::~XP() {
}

const char* XP::getModuleName() {
	return ("XP");
}

void XP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->addLevels(amount);
}