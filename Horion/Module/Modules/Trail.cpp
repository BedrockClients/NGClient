#include "../../DrawUtils.h"
#include "Trail.h"
#include "../ModuleManager.h"

Trail::Trail() : IModule(0x0, Category::GUI, "Leaves a trail behind you") {
	registerBoolSetting("Rainbow", &Rainbow, Rainbow);
	registerBoolSetting("Clear On Disable", &clearondisable, clearondisable);
	registerBoolSetting("Stop Trail", &stopTrail, stopTrail);
}

Trail::~Trail() {
}

static float rcolors[4];

const char* Trail::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (Rainbow) 
			return "Trail [RGB]";
		else
			return "Trail";
	} else
		return "Trail";
}

void Trail::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	vec3_t floorPos = *g_Data.getLocalPlayer()->getPos();
	floorPos.y = g_Data.getLocalPlayer()->getAABB()->lower.y + 0.2f;
	if (!stopTrail) {
		floorPos.y += 0.3f;
		linePoints.push_back(floorPos);
		floorPos.y += 0.2f;
		linePoints1.push_back(floorPos);
		floorPos.y += 0.2f;
		linePoints2.push_back(floorPos);
		floorPos.y += 0.2f;
		linePoints3.push_back(floorPos);
		floorPos.y += 0.2f;
		linePoints4.push_back(floorPos);
		floorPos.y += 0.2f;
		linePoints5.push_back(floorPos);
	}
	float dist = (linePoints.front()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist > 3.2) {
		linePoints.clear();
		linePoints1.clear();
		linePoints2.clear();
		linePoints3.clear();
		linePoints4.clear();
		//linePoints5.clear();
	}
}

void Trail::onLevelRender() {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (!linePoints.empty()) {
	if (Rainbow) 
	DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1); else 
	DrawUtils::setColor(0.f, 1.f, 1.f, 1);
	DrawUtils::drawLinestrip3d(linePoints);
	DrawUtils::drawLinestrip3d(linePoints1);
	DrawUtils::drawLinestrip3d(linePoints2);
	DrawUtils::drawLinestrip3d(linePoints3);
	DrawUtils::drawLinestrip3d(linePoints4);
	//DrawUtils::drawLinestrip3d(linePoints5);
	}
}

void Trail::onDisable() {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (clearondisable)
	linePoints.clear();
}

void Trail::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		// Rainbow colors
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}
			Utils::ApplyRainbow(rcolors, 0.0015f);
	}
}