#include "Disabler.h"

Disabler::Disabler() : IModule('0', Category::SERVER, "Disabler for servers") {
	registerBoolSetting("Hive Speed", &hive, hive);
}

const char* Disabler::getModuleName() {
	return ("Disabler");
}

void Disabler::onTick(C_GameMode* gm) {
}

void Disabler::onMove(C_MoveInputHandler* input) {
}
void Disabler::onSendPacket(C_Packet* packet) {
}