#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "Coordinates.h"

Coordinates::Coordinates(): IModule(0x0, Category::GUI, "Coordinates") {
	registerFloatSetting("Overworld CoordinatesX", &CoordinatesX, CoordinatesX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("Overworld CoordinatesY", &CoordinatesY, CoordinatesY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Nether CoordinatesX", &NetherX, NetherX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("Nether CoordinatesY", &NetherY, NetherY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

Coordinates::~Coordinates() {
}

const char* Coordinates::getModuleName() {
	return ("Coordinates");
}

static float currColor[4];

void Coordinates::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	// rainbow colors
	{
		if (currColor[3] < 1) {
			currColor[0] = 1;
			currColor[1] = 0.2f;
			currColor[2] = 0.2f;
			currColor[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
	}

	// Coordinates
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	float yVal = CoordinatesY;
	float xVal = CoordinatesX;

	static auto hud = moduleMgr->getModule<HudModule>();
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	if (!(g_Data.getLocalPlayer() == nullptr)) {
		std::string Overworld = "Overworld X: " + std::to_string((int)floorf(pos->x)) + " Y: " + std::to_string((int)floorf(pos->y)) + " Z: " + std::to_string((int)floorf(pos->z));
		std::string Nether = "Nether X: " + std::to_string((int)floorf(pos->x / 8)) + " Y: " + std::to_string((int)floorf(pos->y)) + " Z: " + std::to_string((int)floorf(pos->z / 8));
		vec4_t rectPos = vec4_t(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
		vec2_t textPos = vec2_t(xVal, yVal);

		if (hud->rgb) {
			DrawUtils::drawText(vec2_t{textPos}, &Overworld, MC_Color(currColor), scale);
			DrawUtils::drawText(vec2_t{textPos}, &Nether, MC_Color(currColor), scale);
		} else if (hud->surge) {
			DrawUtils::drawText(vec2_t{textPos}, &Overworld, MC_Color(0, 0, 255), scale);
			DrawUtils::drawText(vec2_t{textPos}, &Nether, MC_Color(0, 0, 255), scale);
		} else {
			DrawUtils::drawText(vec2_t{textPos}, &Overworld, MC_Color(184, 0, 255), scale);
			DrawUtils::drawText(vec2_t{textPos}, &Nether, MC_Color(0, 0, 255), scale);
		}
		yVal += f;
	}
}