#include "Mineplex.h"
#include "../ModuleManager.h"

Mineplex::Mineplex() : IModule(0x0, Category::SERVER, "Bypass moevment hacks for Mineplex") {
	registerBoolSetting("DelayMode", &delayMode, delayMode);
	registerIntSetting("DelaySpeed", &speedMod, 2, 1, 10);
}

Mineplex::~Mineplex() {
}

const char* Mineplex::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (delayMode) {
			return "MineplexBypass [Delay]";
		} else
			return "MineplexBypass";
	} else
		return "MineplexBypass";
}

void Mineplex::onWorldTick(C_GameMode* gm) {
	if (!delayMode) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	} else {
		speedMod0++;
		if (speedMod0 = speedMod) {
			speedMod0 = 0;
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		}
	}
}