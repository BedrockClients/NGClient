#include "fps.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

fps::fps() : IModule(0x0, Category::GUI, "Frames Per Second") {
	registerFloatSetting("fpsX", &fpsX, fpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("fpsY", &fpsY, fpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

fps::~fps() {
}

const char* fps::getModuleName() {
	return ("FPS");
}

static float currColor[4];

void fps::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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

	// fps
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	float yVal = fpsY;
	float xVal = fpsX;

	static auto hud = moduleMgr->getModule<HudModule>();
	if (!(g_Data.getLocalPlayer() == nullptr)) {
		std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
		vec4_t rectPos = vec4_t(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
		vec2_t textPos = vec2_t(xVal, yVal);

		if(hud->rgb) {
			DrawUtils::drawText(vec2_t{textPos}, &fpsText, MC_Color(currColor), scale);
		}
		else if (hud->surge) {
			DrawUtils::drawText(vec2_t{textPos}, &fpsText, MC_Color(0, 0, 255), scale);
		}
		else {
			DrawUtils::drawText(vec2_t{textPos}, &fpsText, MC_Color(184, 0, 255), scale);
		}
		yVal += f;
	}
}