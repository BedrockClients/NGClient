#include "Derp.h"
#include "../ModuleManager.h"

Derp::Derp() : IModule(0, Category::PLAYER, "lol you stupid") {
	registerBoolSetting("ihaveastroke", &epicStroke, epicStroke);
	registerBoolSetting("Hive", &hive, hive);
	registerBoolSetting("packet mode", &packetMode, packetMode);
}

Derp::~Derp() {
}

const char* Derp::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (hive) {
			return "Derp [Hive]";
		} else if (epicStroke) {
			return "Derp [Stroke]";
		} else if (packetMode) {
			return "Derp [Packet]";
		} else
			return "Derp";
	} else
		return "Derp";
}

void Derp::onWorldTick(C_GameMode* gm) {
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

float randFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void Derp::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>()&& g_Data.getLocalPlayer() != nullptr && hive && g_Data.isInGame()) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->pitch = randFloat(-90, 90);
		movePacket->yaw = randFloat(-180, 180);
	}
}