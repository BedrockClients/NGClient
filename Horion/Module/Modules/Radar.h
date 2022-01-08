#pragma once
#include "Module.h"
#include "../../DrawUtils.h"
#include <array>
class Radar : public IModule {
public:
	float rcolors[4];
	int size = 100;
	float pixelSize = 2.5f;
	float cent = size / 2.f;
	float pxSize = pixelSize / 2.f;
	float topPad = -1;
	float zoom = 1;
	float pxOpacity = 1;
	bool grid = true;
	float effectiveZoom = 1;
	float angle = 0;
	float c, s;
	vec3_t playerPos;
	float bgOpacity = 0.2f;
	void recalculateScale() {
		effectiveZoom = zoom * (size / 100.f);
		cent = size / 2.f;
		pxSize = pixelSize / 2.f * effectiveZoom;
		topPad = g_Data.getGuiData()->heightGame / 2.f;
	}
	Radar() : IModule(0x0, Category::VISUAL, "Radar") {
	//registerBoolSetting("Show Grid", &grid, true);
	registerIntSetting("Size", &size, size, 50.0f, 200.0f);
	registerFloatSetting("Pixel Size", &pixelSize, pixelSize, 2.0f, 4.0f);
	registerFloatSetting("Zoom", &zoom, zoom, 1.0f / 4.0f, 4.0f);
	registerFloatSetting("Background Opacity", &bgOpacity, bgOpacity, 0.1f, 1.0f);
	registerFloatSetting("Pixel Opacity", &pxOpacity, pxOpacity, 0.1f, 1.0f);
};
	~Radar(){};
	void renderEntity(C_Entity* currentEntity, bool isRegularEntity) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (currentEntity == nullptr)
			return;

		if (currentEntity == player)  // Skip Local player
			return;

		if (!player->canAttack(currentEntity, false))
			return;

		if (!currentEntity->isAlive())
			return;

		if (!Target::isValidTarget(currentEntity))
			return;

		vec3_t* start = currentEntity->getPosOld();
		vec3_t* end = currentEntity->getPos();

		vec3_t lerped = start->lerp(end, DrawUtils::getLerpTime());

		const auto delta = lerped.sub(playerPos);
		const float dist = delta.magnitudexz();

		const vec2_t relPos = vec2_t(
			cent - ((delta.x * c) - (delta.z * s)),
			topPad - ((delta.x * s) + (delta.z * c)));
		if (relPos.x > 0 && relPos.x < size && relPos.y > topPad - cent && relPos.y < topPad + cent) {
			DrawUtils::fillRectangle(vec4_t(relPos.x - pxSize, relPos.y - pxSize, relPos.x + pxSize, relPos.y + pxSize), MC_Color(rcolors[0], rcolors[1], rcolors[2]), pxOpacity);
		}
	}
	// Inherited via IModule
	virtual const char* getModuleName() override { return "Radar"; }
};
