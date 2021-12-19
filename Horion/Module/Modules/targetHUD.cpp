#include "targetHUD.h"

targetHUD::targetHUD() : IModule('L', Category::GUI, "Attacks entities around you automatically") {
	registerBoolSetting("targetHUD", &targetHUDlist, targetHUDlist);
	registerFloatSetting("targetHUD Opacity", &targetHUDopacity, targetHUDopacity, 0.0f, 1.f);
}

targetHUD::~targetHUD() {
	if (g_Data.isInGame()) {
	}
}

const char* targetHUD::getModuleName() {
	return ("targetHUD");
}

static std::vector<C_Entity*> targetList;

void targetHUD::onPostRender(C_MinecraftUIRenderContext* ctx) {
	static auto targetHUDmod = moduleMgr->getModule<targetHUD>();
	if (targetHUDlist && g_Data.isInGame()) {
		vec4_t tempPos = vec4_t(120.f, 5.f, 90.f, 40.f);           //temp pos for the text pos, so we can create a pos that doesn't have player names overlapping from the box to the screen
		vec2_t textPos = vec2_t(tempPos.y, tempPos.x);             //text pos
		vec4_t pos = vec4_t(3.f, 118.f, 75.f + textPos.x, 223.f);  //pos for using
		static float rcolors2[4];                                  // Rainbow color array RGBA
		static float disabledRcolors2[4];                          // Rainbow Colors, but for disabled modules
		static float currColor[4];                                 // ArrayList colors

		// Rainbow color updates
		{
			Utils::ApplyRainbow(rcolors2, 0.001f);  // Increase Hue of rainbow color array
			disabledRcolors2[0] = std::min(1.f, rcolors2[0] * 0.4f + 0.2f);
			disabledRcolors2[1] = std::min(1.f, rcolors2[1] * 0.4f + 0.2f);
			disabledRcolors2[2] = std::min(1.f, rcolors2[2] * 0.4f + 0.2f);
			disabledRcolors2[3] = 1;
		}
		currColor[3] = rcolors2[3];
		Utils::ColorConvertRGBtoHSV(rcolors2[0], rcolors2[1], rcolors2[2], currColor[0], currColor[2], currColor[2]);
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[0], currColor[1]);
		if (!targetList.empty()) {
			std::string name = targetList[0]->getNameTag()->getText();
			std::string distance = "Distance: " + std::to_string((*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
			std::string X = "X: " + std::to_string((targetList[0]->getPos()->x));
			std::string Y = "Y: " + std::to_string((targetList[0]->getPos()->y));
			std::string Z = "Z: " + std::to_string((targetList[0]->getPos()->z));
			std::string DmgTime = "DmgTime: " + std::to_string((targetList[0]->damageTime));
			std::string OnGround = "OnGround: " + std::to_string((targetList[0]->onGround));
			std::string isPlayer = "IsPlayer: " + std::to_string((targetList[0]->isPlayer()));
			std::string height = "height: " + std::to_string((targetList[0]->height));
			std::string entityid = "EntityID: " + std::to_string((targetList[0]->getEntityTypeId()));
			DrawUtils::drawRectangle(pos, currColor, 1.f);
			DrawUtils::fillRectangle(pos, MC_Color(00, 00, 00), targetHUDmod->targetHUDopacity);
			if (!targetList.empty()) {
				DrawUtils::drawText(textPos, &name, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &distance, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &X, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &Y, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &Z, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &DmgTime, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &OnGround, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &isPlayer, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &height, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &entityid, currColor, 1.f);
			}
		}
	}
}