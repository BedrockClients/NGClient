#include "../ModuleManager.h"
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : IModule(0x0, Category::PLAYER, "Replaces Sounds") {
	registerBoolSetting("Random", &random, random);
	registerIntSetting("Sound", &sound, sound, 0, 500);
}

SoundPlayer::~SoundPlayer() {
}

const char* SoundPlayer::getModuleName() {
		return "SoundPlayer";
}

void SoundPlayer::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<LevelSoundEventPacket>()) {
		auto* soundpacket = reinterpret_cast<LevelSoundEventPacket*>(packet);
		if (random)
		soundpacket->sound = (int)(rand() % 500);
		else
		soundpacket->sound = sound;
	}
}