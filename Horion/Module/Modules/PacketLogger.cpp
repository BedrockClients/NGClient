#include "PacketLogger.h"

PacketLogger::PacketLogger() : IModule(0, Category::WORLD, "Logging Packets !") {
}

PacketLogger::~PacketLogger() {
}

const char* PacketLogger::getModuleName() {
	return ("PacketLogger");
}

void PacketLogger::onSendPacket(C_Packet* packet) {
	 if (packet->isInstanceOf<C_PlayerActionPacket>()) {
		auto pk = reinterpret_cast<C_PlayerActionPacket*>(packet);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s action=%i", packet->getName()->getText(), pk->action);
		return;
	}

	 if (packet->isInstanceOf<LevelSoundEventPacket>()) {
		auto pk = reinterpret_cast<LevelSoundEventPacket*>(packet);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s sound=%i", packet->getName()->getText(), pk->sound);
		return;
	}

	if (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") != 0) {
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
	}
}