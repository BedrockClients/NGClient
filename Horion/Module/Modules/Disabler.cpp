#include "Disabler.h"
#include <queue>
#include <chrono>

Disabler::Disabler() : IModule('0', Category::SERVER, "Disabler for servers") {
	registerBoolSetting("Hive Speed", &hive, hive);
}

std::queue<std::pair<NetworkLatencyPacket, unsigned __int64>> latencyPacketQueue;
std::queue<std::pair<NetworkLatencyPacket, unsigned __int64>> emptyPacketQueue;

bool sendingEpicThingy = false;

const char* Disabler::getModuleName() {
	return ("Disabler");
}

void Disabler::onEnable() {
	latencyPacketQueue = emptyPacketQueue;
}

void Disabler::onTick(C_GameMode* gm) {
	unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	while (!latencyPacketQueue.empty() && now - latencyPacketQueue.front().second >= 5000) {
		NetworkLatencyPacket packetToSend = latencyPacketQueue.front().first;
		sendingEpicThingy = true;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&packetToSend);
		sendingEpicThingy = false;
		latencyPacketQueue.pop();
	}
}

void Disabler::onMove(C_MoveInputHandler* input) {
}

void Disabler::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<NetworkLatencyPacket>()) {
		if (sendingEpicThingy == false) {
			NetworkLatencyPacket* currentPacket = (NetworkLatencyPacket)packet;
			unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			latencyPacketQueue.push({ *currentPacket, now });
			currentPacket->timeStamp = 69420;
		}
    }
}