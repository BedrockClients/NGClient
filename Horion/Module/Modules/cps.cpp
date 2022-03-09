#include "cps.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

cps::cps()
	: IModule(0x0, Category::GUI, "Clicks Per Second") {
	registerFloatSetting("cpsX", &cpsX, cpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("cpsY", &cpsY, cpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

cps::~cps() {
}

static float currColor[4];

const char* cps::getModuleName() {
	return ("CPS");
}

void cps::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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

	// CPS
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	float yVal = cpsY;
	float xVal = cpsX;

		static auto partner = moduleMgr->getModule<Partner>();
	if (!(g_Data.getLocalPlayer() == nullptr)) {
		std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
		vec4_t rectPos = vec4_t(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
		vec2_t textPos = vec2_t(xVal, yVal);
		if (partner->surge) {
			DrawUtils::drawText(vec2_t{textPos}, &cpsText, MC_Color(currColor), scale);
		} else if (partner->surge) {
			DrawUtils::drawText(vec2_t{textPos}, &cpsText, MC_Color(0, 0, 255), scale);
		} else {
			DrawUtils::drawText(vec2_t{textPos}, &cpsText, MC_Color(184, 0, 255), scale);
		}
		yVal += f;
	}
}