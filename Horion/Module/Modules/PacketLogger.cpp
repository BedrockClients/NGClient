#include "PacketLogger.h"
#include <iomanip>
#include <basetsd.h>

PacketLogger::PacketLogger() : IModule(0, Category::WORLD, "Logging Packets! (PlayerAuthInput & SubChunkRequest don't display for spam reasons)") {
	registerBoolSetting("Packet Addr", &packetadd, &packetadd);
}

PacketLogger::~PacketLogger() {
}

const char* PacketLogger::getModuleName() {
	return ("PacketLogger");
}

void PacketLogger::onSendPacket(C_Packet* packet) {
	if (packetadd) {
		auto player = g_Data.getLocalPlayer();
		uint64_t currVTable = *(UINT64*)packet;
		std::stringstream stream;
		stream << std::hex << (currVTable - Utils::getBase());
		std::string result(stream.str());
		std::string packetText = packet->getName()->getText() + (std::string) " (Minecraft.Windows.exe+" + result + ")";
		TextHolder txt = TextHolder(packetText);
		player->displayClientMessage(&txt);
	} else {
		if (packet->isInstanceOf<C_PlayerActionPacket>()) {
			auto pk = reinterpret_cast<C_PlayerActionPacket*>(packet);
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s action=%i", packet->getName()->getText(), pk->action);
			return;
		}
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
		if (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") != 0 && strcmp(packet->getName()->getText(), "SubChunkRequestPacket") != 0) {
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
		}
	}
}