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
	if (g_Data.isInGame() && resetViewTick == -1 && redirectMouse) {
		resetViewTick = isThirdPerson;
		if (cameraFacesFront) {
			lastCameraAngle.y += 180;
			lastCameraAngle = lastCameraAngle.normAngles();
			mouseEnd = lastCameraAngle;

			initialViewAngles.y += 180;
			initialViewAngles = initialViewAngles.normAngles();
		} else {
			mouseEnd = lastCameraAngle;
			mouseEnd.y += 180;
		}
	} else if (!g_Data.isInGame()) {
		redirectMouse = false;
	}
	deez = {};
}


void Freelook::onPostRender(C_MinecraftUIRenderContext* mode) {
	if (resetViewTick > 0) {
		resetViewTick--;
	}
}

void Freelook::onTick(C_GameMode* mode) {
	if (resetViewTick == 0) {
		redirectMouse = false;
		resetViewTick = -1;
		auto loc = g_Data.getLocalPlayer();
		vec2_t l = initialViewAngles;
		l = l.sub(mouseEnd).normAngles();
		l.x = initialViewAngles.x - mouseEnd.x;  // dont norm this angle

		l.x *= -1;
		loc->applyTurnDelta(&l);
	}
}
