#include "Freelook.h"

#include "../../../Utils/Logger.h"

Freelook::Freelook() : IModule(0, Category::PLAYER, "Move straight while moving your camera around") {
}
Freelook::~Freelook() {
}
const char* Freelook::getModuleName() {
	return "Freelook";
}
vec2_t mouseEnd = {0, 0};

void Freelook::onEnable() {
	deez = g_Data.getLocalPlayer()->viewAngles;
	redirectMouse = true;
}

void Freelook::onDisable() {
}

void Freelook::onPostRender(C_MinecraftUIRenderContext* mode) {
	if (resetViewTick > 0) {
		resetViewTick--;
	}
}

void Freelook::onTick(C_GameMode* mode) {
}
