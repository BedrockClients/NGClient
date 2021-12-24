#include "PacketLogger.h"

PacketLogger::PacketLogger() : IModule(0, Category::WORLD, "Logging Packets !") {
}

PacketLogger::~PacketLogger() {
}

const char* PacketLogger::getModuleName() {
	return ("PacketLogger");
}

void PacketLogger::onSendPacket(C_Packet* packet) {
	 //if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		//auto pk = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		//g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s action=%i", packet->getName()->getText(), pk->velocity); not rlly needed rn
	//	return;
	//}

	 if (packet->isInstanceOf<LevelSoundEventPacket>()) {
		auto pk = reinterpret_cast<LevelSoundEventPacket*>(packet);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s sound=%i", packet->getName()->getText(), pk->sound);
		return;
	}

	if (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") != 0) {
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
	}
}