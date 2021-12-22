#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule('O', Category::VISUAL, "Makes it easier to find entities around you") {
	registerBoolSetting("rainbow", &doRainbow, doRainbow);
	registerBoolSetting("MobEsp", &isMobEsp, isMobEsp);
	registerBoolSetting("2d", &is2d, is2d);
	registerBoolSetting("Zephyr ESP", &iszephyr, iszephyr);
	registerBoolSetting("Better ESP", &betterESP, betterESP);
	registerBoolSetting("GodsEye ESP", &circle, circle);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (isMobEsp) {
			return "ESP [Mob]";
		} else if (circle) {
			return "ESP [Circle]";
		} else if (betterESP) {
			return "ESP [3D]";
		} else if (is2d || is2d) {
			return "ESP [2D]";
		} else if (iszephyr || is2d) {
			return "ESP [Zephyr]";
		} else if (doRainbow) {
			return "ESP [RGB]";
		} else return "ESP";
	} else
		return "ESP";
}

static float rcolors[4];
std::vector<vec3_ti> lastPos;
void ESP::onEnable() {
	lastPos.clear();
}
void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();

	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent == localPlayer)
		return;
	if (ent->timeSinceDeath > 0)
		return;
	static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
	if (!noFriendsModule->isEnabled() && FriendList::findPlayer(ent->getNameTag()->getText())) {
		DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	} else if (Target::isValidTarget(ent)) {
		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		else
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	} else if (espMod->isMobEsp) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!localPlayer->canAttack(ent, false))
			return;
		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		else
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	} else
		return;
	if (espMod->is2d)
		DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()) * 3.f)));
	else if (espMod->iszephyr)
		DrawUtils::drawZephyr(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()) * 3.f)));
	else if (espMod->betterESP)
		DrawUtils::drawBetterESP(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
	else
		DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
}

void ESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	for (auto pos : lastPos) {
		DrawUtils::drawBox(pos.toFloatVector(), pos.add(1, 1, 1).toFloatVector(), 1, false);
	}
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		// Rainbow colors
		{
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}

			Utils::ApplyRainbow(rcolors, 0.0015f);
		}

		g_Data.forEachEntity(doRenderStuff);
	}
}

float Circle = 0;
void ESP::onLevelRender() {
	if (circle) {
		Circle++;
		if (doRainbow) {
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1);
		} else
			DrawUtils::setColor(1.f, 1.f, 1.f, 1);
		g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
			static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
			if (!noFriendsModule->isEnabled() && !FriendList::findPlayer(ent->getNameTag()->getText())) {
				if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
					vec3_t Lines[36];
					for (int i = 0; i < 36; i++) {
						Lines[i] = {sinf((i * 9) / (120 / PI)), 0.f, cosf((i * 9) / (120 / PI))};
					}
					std::vector<vec3_t> posList;
					vec3_t pos = ent->getPosOld()->lerp(ent->getPos(), DrawUtils::getLerpTime());
					pos.y -= 1.62f;
					pos.y += sin((Circle / 60) * PI) + 1;
					for (auto& Booty : Lines) {
						vec3_t curPos(pos.x, pos.y, pos.z);
						posList.push_back(curPos.add(Booty));
					}
					DrawUtils::drawLinestrip3d(posList);
				}
			}
		});
	}
}