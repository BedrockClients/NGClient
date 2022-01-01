#pragma once
#include "Module.h"
class AutoSneak : public IModule {
public:
	bool doSilent = false;
	AutoSneak() : IModule(0, Category::MOVEMENT, "Automatically sneak without holding the key") {
		registerBoolSetting("silent", &doSilent, doSilent);
	}
	~AutoSneak(){};

	virtual const char* getModuleName() override { return ("AutoSneak"); }
	virtual void onWorldTick(C_GameMode* gm) override {
		if (!doSilent)
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
	}
	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			return;

		if (!doSilent) {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
			return;
		}

		C_PlayerActionPacket p;
		p.action = 12;  //stop crouch packet
		p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			return;  //fixed crash

		if (doSilent) {
			C_PlayerActionPacket p;
			p.action = 11;  //start crouch packet
			p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		}
	}
};