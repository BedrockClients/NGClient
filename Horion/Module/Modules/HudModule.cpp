#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::GUI, "Displays Hud") {
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("MSG", &Msg, Msg);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerBoolSetting("Coordinates", &coordinates, coordinates);
	registerBoolSetting("Bools", &bools, bools);
	registerBoolSetting("Keybinds", &keybinds, keybinds);
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor);
	registerBoolSetting("Show FPS", &fps, fps);
	registerBoolSetting("Show CPS", &cps, cps);
	registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerFloatSetting("Opacity", &opacity, opacity, 0.0f, 1.f);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

HudModule::~HudModule() {
}

static float rcolors[4];

const char* HudModule::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (rgb || Msg || clickToggle || watermark || coordinates || keybinds || keystrokes || displayArmor || fps || cps || alwaysShow) {
			return "HUD [Customised]";
		} else
			return "HUD";
	} else
		return "HUD";
}
void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto Surge = moduleMgr->getModule<ClickGuiMod>();
	// rainbow colors
	{
		if (rcolors[3] < 1) {
			rcolors[0] = 0.2f;
			rcolors[1] = 0.2f;
			rcolors[2] = 1.f;
			rcolors[3] = 1;
		}
		Utils::ApplyRainbow(rcolors, 0.0015f);
	}
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;
	if(tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;
         { // FPS
		if (!(g_Data.getLocalPlayer() == nullptr || !fps)) {
			std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.00f);
			if (rgb) {
				DrawUtils::drawText(textPos, &fpsText, MC_Color(rcolors), scale);
			} else {
				if (Surge->surge)
				DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
				else
				DrawUtils::drawText(textPos, &fpsText, MC_Color(184, 0, 255), scale);
			}
			startY += f;
		}
	}
	{  // CPS
		if (!(g_Data.getLocalPlayer() == nullptr || !cps)) {
			std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.0f);
			if (rgb) {
				DrawUtils::drawText(textPos, &cpsText, MC_Color(rcolors), scale);
			} else {
				if (Surge->surge)
				DrawUtils::drawText(textPos, &cpsText, MC_Color(0, 0, 255), scale);
				else
				DrawUtils::drawText(textPos, &cpsText, MC_Color(184, 0, 255), scale);
			}

			startY += f;
		}
	}
	{  // Hello thing
		if (!(g_Data.getLocalPlayer() == nullptr || !Msg || !GameData::canUseMoveKeys())) {
			if (Surge->surge) {
				std::string fpsText = "sup bitch";
				vec4_t rectPos = vec4_t(0.5f, startY + 30.f * scale, len, startY + 100.f * scale);
				vec2_t textPos = vec2_t(rectPos.y + 250.5f, rectPos.x + 4.f);
				if (rgb) {
					DrawUtils::drawText(textPos, &fpsText, MC_Color(rcolors), scale);
				} else {
					if (Surge->surge)
						DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
					else
						DrawUtils::drawText(textPos, &fpsText, MC_Color(184, 0, 255), scale);
				}
				if (rcolors[3] < 1) {
					rcolors[0] = 0.2f;
					rcolors[1] = 0.2f;
					rcolors[2] = 1.f;
					rcolors[3] = 1;
				}
			} else {
				std::string fpsText = "NG Client on Top!";
				vec4_t rectPos = vec4_t(0.5f, startY + 30.f * scale, len, startY + 100.f * scale);
				vec2_t textPos = vec2_t(rectPos.y + 250.5f, rectPos.x + 4.f);
				if (rgb) {
					DrawUtils::drawText(textPos, &fpsText, MC_Color(rcolors), scale);
				} else {
					if (Surge->surge)
						DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
					else
						DrawUtils::drawText(textPos, &fpsText, MC_Color(184, 0, 255), scale);
				}
				if (rcolors[3] < 1) {
					rcolors[0] = 0.2f;
					rcolors[1] = 0.2f;
					rcolors[2] = 1.f;
					rcolors[3] = 1;
				}
			}
		}
	}
	{  // Coordinates
		if (!(g_Data.getLocalPlayer() == nullptr || !coordinates)) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();

			std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
			std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y));
			std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.0f);
			if (rgb) {
				DrawUtils::drawText(textPos, &coordsX, MC_Color(rcolors), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsY, MC_Color(rcolors), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsZ, MC_Color(rcolors), scale);
			} else {
				if (Surge->surge) {
					DrawUtils::drawText(textPos, &coordsX, MC_Color(0, 0, 255), scale);
					textPos.y += f;
					DrawUtils::drawText(textPos, &coordsY, MC_Color(0, 0, 255), scale);
					textPos.y += f;
					DrawUtils::drawText(textPos, &coordsZ, MC_Color(0, 0, 255), scale);
				} else {
					DrawUtils::drawText(textPos, &coordsX, MC_Color(184, 0, 255), scale);
					textPos.y += f;
					DrawUtils::drawText(textPos, &coordsY, MC_Color(184, 0, 255), scale);
					textPos.y += f;
					DrawUtils::drawText(textPos, &coordsZ, MC_Color(184, 0, 255), scale);
				}
			}
		}
	}
	{	// ArmorHUD

		if (!(g_Data.getLocalPlayer() == nullptr || !displayArmor || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.25f;
			static float constexpr spacing = scale + 15.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float x = windowSize.x / 2.f + 5.f;
			float y = windowSize.y - 57.5f;
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, vec2_t(x, y), opacity, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			//x += scale * spacing;
			if (item->isValid())
				DrawUtils::drawItem(item, vec2_t(x, y), opacity, scale, item->isEnchanted());
		}
	}
	{  // Keystrokes
		if (!(g_Data.getLocalPlayer() == nullptr || !keystrokes || !GameData::canUseMoveKeys())) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			if (Surge->surge) {
				DrawUtils::setColor(0, 0, 255, 1);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 84));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 40));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(10.f, windowSize.y - 25));
				DrawUtils::drawRightMouseKeystroke(vec2_t(43.f, windowSize.y - 25));
			}
			if (rgb) {
				DrawUtils::setColor(*rcolors, *rcolors, *rcolors, *rcolors);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 84));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 40));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(10.f, windowSize.y - 25));
				DrawUtils::drawRightMouseKeystroke(vec2_t(43.f, windowSize.y - 25));
			} else {
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 84));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 40));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(10.f, windowSize.y - 25));
				DrawUtils::drawRightMouseKeystroke(vec2_t(43.f, windowSize.y - 25));
			}
		}
	}
}