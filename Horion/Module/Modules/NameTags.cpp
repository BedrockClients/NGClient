#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

NameTags::NameTags() : IModule(0, Category::VISUAL, "Shows betterar aways") {
	registerBoolSetting("Underline", &underline, underline);
	registerBoolSetting("Armor", &displayArmor, displayArmor);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (underline) {
			return "NameTags [Line]";
		} else if (displayArmor) {
			return "NameTags [Armor]";
		} else
			return "NameTags";
	} else
		return "NameTags";
}

void drawNameTags(C_Entity* ent, bool) {
	static auto freeMod = moduleMgr->getModule<Freecam>();
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();
	if (freeMod->isEnabled()) {
			if (ent->timeSinceDeath > 0)
				return;
			if (ent->getNameTag()->getTextLength() < 1)
				return;
			if (Target::isValidTarget(ent) && nameTagsMod != nullptr) {
				nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
				float dist = ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos());
				DrawUtils::drawNameTags(ent, fmax(0.6f, 3.f / dist));
				DrawUtils::flush();
			}
	} else {
		if (ent != localPlayer) {
			if (ent->timeSinceDeath > 0)
				return;
			if (ent->getNameTag()->getTextLength() < 1)
				return;
			if (Target::isValidTarget(ent) && nameTagsMod != nullptr) {
				nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
				float dist = ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos());
				DrawUtils::drawNameTags(ent, fmax(0.6f, 3.f / dist));
				DrawUtils::flush();
			}
		}
	}
}

void NameTags::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer == nullptr || !GameData::canUseMoveKeys()) return;

	if (ingameNametagSetting)
		if (!gotPrevSetting) {
			lastSetting = *ingameNametagSetting;
			gotPrevSetting = true;
			*ingameNametagSetting = false;
		} else
			*ingameNametagSetting = false;  //disable other ppl's nametags

	g_Data.forEachEntity(drawNameTags);
}

void NameTags::onDisable() {
	if (ingameNametagSetting && gotPrevSetting) {
		*ingameNametagSetting = lastSetting;
		gotPrevSetting = false;
	}
	*ingameNametagSetting = true;
}