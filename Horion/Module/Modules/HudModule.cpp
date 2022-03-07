#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::GUI, "Displays Hud") {
	//Surge
	registerBoolSetting("Surge", &surge, surge);
	registerBoolSetting("Buttons", &Buttons, Buttons);
	registerBoolSetting("cords", &Hud, Hud);
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("MSG", &Msg, Msg);
	registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor);
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
		if (surge)
			return "Hud [Surge]";
		else if (rgb || Msg || watermark || keybinds || keystrokes || displayArmor || alwaysShow) {
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
		if (!(g_Data.getLocalPlayer() == nullptr || !Msg || !GameData::canUseMoveKeys())) {
			if (surge) {
				std::string fpsText = "sup bitch";
					if (surge)
						DrawUtils::drawText(vec2_t(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(0, 0, 255), scale);
			} else {
				std::string fpsText = "NG Client on Top!";
					if (!surge)
						DrawUtils::drawText(vec2_t(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(184, 0, 255), scale);
			}
		}
	}

	// ArmorHUD
	if (!(g_Data.getLocalPlayer() == nullptr || !displayArmor || !GameData::canUseMoveKeys())) {
		static float constexpr scale = 1.f;
		static float constexpr spacingy = scale + 15.f;
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		float x = windowSize.x - windowSize.x;
		float y = windowSize.y / 2 - 20.f;
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
			std::string coordsall = "Overworld X: " + std::to_string((int)floorf(pos->x)) + " Y: " + std::to_string((int)floorf(pos->y)) + " Z: " + std::to_string((int)floorf(pos->z));
			std::string Ncoordsall = "Nether X: " + std::to_string((int)floorf(pos->x/8)) + " Y: " + std::to_string((int)floorf(pos->y)) + " Z: " + std::to_string((int)floorf(pos->z/8));
			auto Nx = windowSize.x / 2.f - 210.f;
			auto Ny = windowSize.y - 55.f;
			auto x = windowSize.x / 2.f - 210.f;
			auto y = windowSize.y - 45.f;

			static float constexpr scale = 1.f;
			static float constexpr spacing = scale + 15.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float xArmor = windowSize.x / 2.f - 210.f;
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
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(currColor), scale);
				DrawUtils::drawText(vec2_t{Nx, Ny}, &Ncoordsall, MC_Color(currColor), scale);
			}else
			if (surge) {
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(0, 0, 255), scale);
				DrawUtils::drawText(vec2_t{Nx, Ny}, &Ncoordsall, MC_Color(0, 0, 255), scale);
			} else {
				DrawUtils::drawText(vec2_t{x, y}, &coordsall, MC_Color(184, 0, 255), scale);
				DrawUtils::drawText(vec2_t{Nx, Ny}, &Ncoordsall, MC_Color(184, 0, 255), scale);
			}
		}
	}

	{  // Keystrokes
		if (!(g_Data.getLocalPlayer() == nullptr || !keystrokes || !GameData::canUseMoveKeys())) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			if (surge) {
				DrawUtils::setColor(0, 0, 255, 1);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 93));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(4.f, windowSize.y - 50));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(4.f, windowSize.y - 37));
				DrawUtils::drawRightMouseKeystroke(vec2_t(37.f, windowSize.y - 37));
				DrawUtils::CPS(vec2_t(4.f, windowSize.y - 15));
			}
			if (rgb) {
				DrawUtils::setColor(*currColor, *currColor, *currColor, *currColor);
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 93));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(4.f, windowSize.y - 50));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(4.f, windowSize.y - 37));
				DrawUtils::drawRightMouseKeystroke(vec2_t(37.f, windowSize.y - 37));
				DrawUtils::CPS(vec2_t(4.f, windowSize.y - 15));
			} else {
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(26.f, windowSize.y - 93));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(4.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(26.f, windowSize.y - 71));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(48.f, windowSize.y - 71));
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
