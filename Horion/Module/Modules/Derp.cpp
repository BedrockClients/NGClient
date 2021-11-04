#include "Derp.h"

Derp::Derp() : IModule(0, Category::PLAYER, "lol you stupid") {
	registerBoolSetting("ihaveastroke", &epicStroke, epicStroke);
	registerBoolSetting("Hive", &hive, hive);
	registerBoolSetting("packet mode", &packetMode, packetMode);
}

Derp::~Derp() {
}

const char* Derp::getModuleName() {
	return "Derp";
}

void Derp::onTick(C_GameMode* gm) {
	if (packetMode) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		if (epicStroke && !hive) {
			auto player = g_Data.getLocalPlayer();
			player->yaw = player->bodyYaw + 180;
			p.pitch = (float)(rand() % 360);
			p.yaw = (float)(rand() % 360);
		} else {
			auto player = g_Data.getLocalPlayer();
			player->yaw = player->bodyYaw + 180;
			p.pitch = (float)(counter % 360);
			p.yaw = (float)(counter % 360);
		}
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	} else {
		if (epicStroke && !hive) {
			auto player = g_Data.getLocalPlayer();
			player->yaw = player->bodyYaw + 180;
			gm->player->pitch = (float)(rand() % 360);
			gm->player->bodyYaw = (float)(rand() % 360);
		} else if (!hive) {
			auto player = g_Data.getLocalPlayer();
			player->yaw = player->bodyYaw - 180;
		}
	}

	if (counter <= 360)
		counter++;
	else
		counter = 0;
}
void Derp::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && hive) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		auto player = g_Data.getLocalPlayer();
		movePacket->headYaw = (float)(rand() % 360);
		movePacket->yaw = (float)(rand() % 360);
		movePacket->headYaw = movePacket->yaw;
		movePacket->yaw = movePacket->headYaw;
	}
}