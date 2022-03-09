#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::GUI, "Displays Hud") {
	registerBoolSetting("Buttons", &Buttons, Buttons);
	registerBoolSetting("cords", &Hud, Hud);
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("MSG", &Msg, Msg);
	registerBoolSetting("Keystrokes RGB", &keybindsRGB, keybindsRGB);
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("Show Second Names", &displaySecondHalf, displaySecondHalf);
	registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerFloatSetting("Opacity", &opacity, opacity, 0.0f, 1.f);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	// registerBoolSetting("Notifications", &notifications, notifications);
	//registerBoolSetting("Bools", &bools, bools);
}

HudModule::~HudModule() {
}

static float currColor[4];

const char* HudModule::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
	if (rgb || Msg || watermark || keybinds || keystrokes || alwaysShow) {
			return "HUD [Customised]";
		} else
			return "HUD";
	} else
		return "HUD";
}

void HudModule::onTick(C_GameMode* gm) {
}

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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

	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;
	if (tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;

	{  // Hello thing
		static auto partner = moduleMgr->getModule<Partner>();
		if (!(g_Data.getLocalPlayer() == nullptr || !Msg || !GameData::canUseMoveKeys())) {
			if (partner->surge) {
				std::string fpsText = "sup bitch";
				if (partner->surge)
						DrawUtils::drawText(vec2_t(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(0, 0, 255), scale);
			} else {
				std::string fpsText = "NG Client on Top!";
				if (!partner->surge)
						DrawUtils::drawText(vec2_t(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(184, 0, 255), scale);
			}
		}
	}

	{  // Keystrokes
		if (!(g_Data.getLocalPlayer() == nullptr || !keystrokes || !GameData::canUseMoveKeys())) {
			static auto partner = moduleMgr->getModule<Partner>();
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			if (partner->surge) {
				DrawUtils::setColor(0, 0, 255, 1);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 94));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(4.f, windowSize.y - 50));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(4.f, windowSize.y - 37));
				DrawUtils::drawRightMouseKeystroke(vec2_t(37.f, windowSize.y - 37));
				DrawUtils::CPS(vec2_t(4.f, windowSize.y - 15));
			}
			if (rgb) {
				DrawUtils::setColor(*currColor, *currColor, *currColor, *currColor);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 94));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(4.f, windowSize.y - 50));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(4.f, windowSize.y - 37));
				DrawUtils::drawRightMouseKeystroke(vec2_t(37.f, windowSize.y - 37));
				DrawUtils::CPS(vec2_t(4.f, windowSize.y - 15));
			} else {
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 94));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 72));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(4.f, windowSize.y - 50));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(4.f, windowSize.y - 37));
				DrawUtils::drawRightMouseKeystroke(vec2_t(37.f, windowSize.y - 37));
				DrawUtils::CPS(vec2_t(4.f, windowSize.y - 15));
			}
		}
	}
}
void HudModule::onDisable() {
}
