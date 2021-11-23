#include "swimspeed.h"

swim::swim() : IModule(0, Category::MOVEMENT, "Swim Speed") {
	registerFloatSetting("Swim Speed", &speed, speed, 0.21f, 2.f);
}

swim::~swim() {
}

const char* swim::getModuleName() {
	return "Swim Speed";
}

void swim::onTick(C_GameMode * gm) {
	if (speed) {
		*g_Data.getClientInstance()->minecraft->timer = 72.f * speed;
	}
}

void swim::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}