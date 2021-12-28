#include "AntiVoid.h"

AntiVoid::AntiVoid() : IModule(0, Category::MOVEMENT, "Automatically teleports you back up if you fall down more than X blocks") {
	registerEnumSetting("Mode", &mode, 0);
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Teleport", 0))
			   .addEntry(EnumEntry("Bounce", 1));
	registerIntSetting("distance", &distance, distance, 1, 20);
}

AntiVoid::~AntiVoid() {
}

const char* AntiVoid::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (mode.selected == 0) {
			return "AntiVoid [Teleport]";
		} else if (mode.selected == 1) {
			return "Antivoid [Bounce]";
		} else
			return "Antivoid";
	} else
		return "Antivoid";
}

void AntiVoid::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	if (player->region->getBlock(blockBelow)->blockLegacy->material->isSolid && player->onGround) {
		orgipos = *player->getPos();
	}
	if (player->fallDistance >= distance) {
		if (mode.selected == 0) {
			player->setPos(orgipos);
			static auto hopMod = moduleMgr->getModule<Bhop>();
			static auto speedMod = moduleMgr->getModule<Speed>();
			static auto scaffMod = moduleMgr->getModule<Scaffold>();
			static auto surge = moduleMgr->getModule<ClickGuiMod>();
			hopMod->setEnabled(false);
			speedMod->setEnabled(false);
			if (!scaffMod->isEnabled())
				scaffMod->setEnabled(true);
			if (surge->surge)
				g_Data.getGuiData()->displayClientMessageF("[%sAntivoid%s] %sDisabled Speed, Bhop, and enabled Scaffold%s", BLUE, WHITE, BLUE, WHITE, configMgr, WHITE);
			else
				g_Data.getGuiData()->displayClientMessageF("[%sAntivoid%s] %sDisabled Speed, Bhop, and enabled Scaffold%s", LIGHT_PURPLE, WHITE, LIGHT_PURPLE, WHITE, configMgr, WHITE);
		}
		if (mode.selected == 1) {
			float dist = gm->player->getPos()->dist(orgipos);
			g_Data.getLocalPlayer()->lerpMotion(vec3_t(0, 1, 0));
		}
	}
}