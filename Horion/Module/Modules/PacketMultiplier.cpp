#include "PacketMultiplier.h"

PacketMultiplier::PacketMultiplier() : IModule(0, Category::SERVER, "funni packet exploit") {
	registerIntSetting("Multiplier", &multiplier, multiplier, 1, 10);
}
PacketMultiplier::~PacketMultiplier() {
}
const char* PacketMultiplier::getModuleName() {
	return "PacketMultiplier";
}