#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::GUI, "Displays Hud") {
	registerBoolSetting("HUD", &Hud, Hud);
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("MSG", &Msg, Msg);
	registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor); //it does not render in a random spot I render on side of your screen
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerBoolSetting("Bools", &bools, bools);
	registerBoolSetting("Keybinds", &keybinds, keybinds);
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
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
	if (tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;

	{  // Hello thing
		if (!(g_Data.getLocalPlayer() == nullptr || !Msg || !GameData::canUseMoveKeys())) {
			if (Surge->surge) {
				std::string fpsText = "sup bitch";
				vec4_t rectPos = vec4_t(0.5f, startY + 30.f * scale, len, startY + 100.f * scale);
				vec2_t textPos = vec2_t(rectPos.y + 250.5f, rectPos.x + 4.f);
				{
					if (Surge->surge)
						DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
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
				{
					if (Surge->surge)
						DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
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

	// ArmorHUD
	if (!(g_Data.getLocalPlayer() == nullptr || !displayArmor || !GameData::canUseMoveKeys())) {
		static float constexpr scale = 1.f;
		static float constexpr spacingy = scale + 15.f;
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		float x = windowSize.x / 2.f - 320.f;
		float y = windowSize.y - 240.f;
		for (int i = 0; i < 4; i++) {
			C_ItemStack* stack = player->getArmor(i);
			if (stack->isValid()) {
				DrawUtils::drawItem(stack, vec2_t(x, y), opacity, scale, stack->isEnchanted());
				y += scale * spacingy;
			}
		}
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
		if (item->isValid())
			DrawUtils::drawItem(item, vec2_t(x, y), opacity, scale, item->isEnchanted());
	}

	{  // Hud
		if (!(g_Data.getLocalPlayer() == nullptr || !Hud || !GameData::canUseMoveKeys())) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			std::string coordsall = "X: " + std::to_string((int)floorf(pos->x)) + " Y: " + std::to_string((int)floorf(pos->y)) + " Z: " + std::to_string((int)floorf(pos->z));
			std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
			std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
			auto xcpsText = windowSize.x / 2.f - 180.f;
			auto ycpsText = windowSize.y - 35.f;
			auto xfpsText = windowSize.x / 2.f - 180.f;
			auto yfpsText = windowSize.y - 45.f;
			auto x = windowSize.x / 2.f - 180.f;
			auto y = windowSize.y - 25.f;

			static float constexpr scale = 1.f;
			static float constexpr spacing = scale + 15.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float xArmor = windowSize.x / 2.f - 180.f;
			float yArmor = windowSize.y - 17.f;
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, vec2_t(xArmor, yArmor), opacity, scale, stack->isEnchanted());
					xArmor += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->isValid())
				DrawUtils::drawItem(item, vec2_t(xArmor, yArmor), opacity, scale, item->isEnchanted());
			if (rgb) {
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(rcolors), scale);
				DrawUtils::drawText(vec2_t{xfpsText, yfpsText}, &fpsText, MC_Color(rcolors), scale);
				DrawUtils::drawText(vec2_t{xcpsText, ycpsText}, &cpsText, MC_Color(rcolors), scale);
			}else
			if (Surge->surge) {
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(0, 0, 255), scale);
				DrawUtils::drawText(vec2_t{xfpsText, yfpsText}, &fpsText, MC_Color(0, 0, 255), scale);
				DrawUtils::drawText(vec2_t{xcpsText, ycpsText}, &cpsText, MC_Color(0, 0, 255), scale);
			} else {
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(184, 0, 255), scale);
				DrawUtils::drawText(vec2_t{xfpsText, yfpsText}, &fpsText, MC_Color(184, 0, 255), scale);
				DrawUtils::drawText(vec2_t{xcpsText, ycpsText}, &cpsText, MC_Color(184, 0, 255), scale);
			}
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