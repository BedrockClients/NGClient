#pragma once
#include "Module.h"
#include "../ModuleManager.h"
class SoundPlayer : public IModule {
private:
	bool random = false;
	int sound = 0;

public:
	SoundPlayer() : IModule(0x0, Category::PLAYER, "Replaces Sounds") {
		registerBoolSetting("Random", &random, random);
		registerIntSetting("Sound", &sound, sound, 0, 500);
	};
	~SoundPlayer() {};
	// Inherited via IModule
	virtual void onSendPacket(C_Packet* packet) {
		if (packet->isInstanceOf<LevelSoundEventPacket>()) {
			auto* soundpacket = reinterpret_cast<LevelSoundEventPacket*>(packet);
			if (random)
				soundpacket->sound = (int)(rand() % 500);
			else
				soundpacket->sound = sound;
		}
	}

	virtual const char* getModuleName() override {
		return "SoundPlayer";
	}
};