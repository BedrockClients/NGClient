#include "Timer.h"

Timer::Timer() : IModule(0, Category::PLAYER, "Increase the ticks per second") {
	registerIntSetting("ticks per second", &timer, timer, 0, 30);
}

Timer::~Timer() {
}

const char* Timer::getModuleName() {
	return ("Timer");
}

void Timer::onTick(C_GameMode* gm) {
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(timer);
}

void Timer::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}
