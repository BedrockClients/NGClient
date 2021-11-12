#include "Killaura.h"

Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	registerFloatSetting("range", &range, range, 2.f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("Info", &info, info);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerBoolSetting("Rotations", &rotations, rotations);
	registerBoolSetting("Sexy Rotations", &sexy, sexy);
	registerBoolSetting("Silent Rotations", &silent, silent);
}

Killaura::~Killaura() {
}

const char* Killaura::getModuleName() {
	return ("Killaura");
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetList;
float rcolorrs[4];
float Outline = 0;
void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->width <= 0.10f || currentEntity->height <= 0.10f)  // Don't hit this pesky antibot on 2b2e.org
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity->getEntityTypeId() == 69)  // xp
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::findWeapon() {
	if (g_Data.isInGame()) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		float damage = 0;
		int slot = supplies->selectedHotbarSlot;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				float currentDamage = stack->getAttackingDamageWithEnchants();
				if (currentDamage > damage) {
					damage = currentDamage;
					slot = n;
				}
			}
		}
		supplies->selectedHotbarSlot = slot;
	}
}

void Killaura::onTick(C_GameMode* gm) {
	targetListA = targetList.empty();
	if (g_Data.isInGame()) {
		g_Data.forEachEntity(findEntity);
		if (autoweapon) findWeapon();
		if (!targetList.empty()) {
			Odelay++;
			if (Odelay >= delay) {
				if (isMulti) {
					for (auto& i : targetList) {
						if (!(i->damageTime > 1 && hurttime)) {
							g_Data.getLocalPlayer()->swing();
							g_Data.getCGameMode()->attack(i);
						}
					}
				} else {
					if (!(targetList[0]->damageTime > 1 && hurttime)) {
						g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(targetList[0]);
					}
				}
				Odelay = 0;
			}
			if (rotations) {
				auto player = g_Data.getLocalPlayer();
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				player->bodyYaw = angle.y;
			}
		}
	}
}

void Killaura::onLevelRender() {
	targetListA = targetList.empty();
	if (g_Data.isInGame()) {
		targetList.clear();
		g_Data.forEachEntity(findEntity);

		if (!targetList.empty()) {
			if (sexy) {
				joe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				auto player = g_Data.getLocalPlayer();
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				player->bodyYaw = angle.x;
				player->bodyYaw = angle.y;
			}
			int prevSlot;
			if (autoweapon) {
				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				prevSlot = supplies->selectedHotbarSlot;
				auto FinishSelect = true;
				auto inv = supplies->inventory;
				for (int n = 0; n < 9; n++) {
					C_ItemStack* stack = inv->getItemStack(n);
					if (stack->item != nullptr) {
						if (stack->getItem()->isWeapon()) {
							if (prevSlot != n)
								supplies->selectedHotbarSlot = n;
							return;
						}
					}
				}
			}
		}
		auto esp = moduleMgr->getModule<ESP>();
		if (outline) {
			Outline++;
			if (esp->doRainbow) {
				DrawUtils::setColor(rcolorrs[0], rcolorrs[1], rcolorrs[2], 1);
			} else
				DrawUtils::setColor(1.f, 1.f, 1.f, 1);
			targetList.clear();
			g_Data.forEachEntity(findEntity);

			if (!targetList.empty()) {
				static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
				if (!noFriendsModule->isEnabled() && !FriendList::findPlayer(targetList[0]->getNameTag()->getText())) {
					if (targetList[0] != g_Data.getLocalPlayer() && Target::isValidTarget(targetList[0])) {
						vec3_t Lines[36];
						for (int i = 0; i < 36; i++) {
							Lines[i] = {sinf((i * 9) / (120 / PI)), 0.f, cosf((i * 9) / (120 / PI))};
						}
						std::vector<vec3_t> posList;
						vec3_t pos = targetList[0]->getPosOld()->lerp(targetList[0]->getPos(), DrawUtils::getLerpTime());
						pos.y -= 1.62f;
						pos.y += sin((Outline / 60) * PI) + 1;
						for (auto& Booty : Lines) {
							vec3_t curPos(pos.x, pos.y, pos.z);
							posList.push_back(curPos.add(Booty));
						}
						DrawUtils::drawLinestrip3d(posList);
					}
				}
			}
		}
	}
	if (!g_Data.isInGame())
		setEnabled(false);
}

void Killaura::onEnable() {
	targetList.clear();
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}
void Killaura::onDisable() {
	targetList.clear();
}
	void Killaura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {

}

void Killaura::onPostRender(C_MinecraftUIRenderContext* ctx) {
	static auto Info = moduleMgr->getModule<Killaura>();

	static auto Killauramod = moduleMgr->getModule<Killaura>();
	if (!targetList.empty() && g_Data.isInGame() && Info->info){
				vec4_t tempPos = vec4_t(120.f, 5.f, 90.f, 40.f);  //temp pos for the text pos, so we can create a pos that doesn't have player names overlapping from the box to the screen
				vec2_t textPos = vec2_t(tempPos.y, tempPos.x);    //text pos
				static float rcolors2[4];                         // Rainbow color array RGBA
				static float disabledRcolors2[4];                 // Rainbow Colors, but for disabled modules
				static float currColor[4];                        // ArrayList colors

				// Rainbow color updates
					Utils::ApplyRainbow(rcolors2, 0.001f);  // Increase Hue of rainbow color array
					disabledRcolors2[0] = std::min(1.f, rcolors2[0] * 0.4f + 0.2f);
					disabledRcolors2[1] = std::min(1.f, rcolors2[1] * 0.4f + 0.2f);
					disabledRcolors2[2] = std::min(1.f, rcolors2[2] * 0.4f + 0.2f);
					disabledRcolors2[3] = 1;
				currColor[3] = rcolors2[3];
				Utils::ColorConvertRGBtoHSV(rcolors2[0], rcolors2[1], rcolors2[2], currColor[0], currColor[2], currColor[2]);
				Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[0], currColor[1]);
				std::string name = targetList[0]->getNameTag()->getText();
				std::string distance = "Distance: " + std::to_string((*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
				std::string X = "X: " + std::to_string((targetList[0]->getPos()->x));
				std::string Y = "Y: " + std::to_string((targetList[0]->getPos()->y));
				std::string Z = "Z: " + std::to_string((targetList[0]->getPos()->z));
				std::string DmgTime = "DmgTime: " + std::to_string((targetList[0]->damageTime));
				std::string OnGround = "OnGround: " + std::to_string((targetList[0]->onGround));
				std::string height = "height: " + std::to_string((targetList[0]->height));
				std::string entityid = "EntityID: " + std::to_string((targetList[0]->getEntityTypeId()));
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
				DrawUtils::drawText(textPos, &height, currColor, 1.f);
				textPos.y += 10.f;
				DrawUtils::drawText(textPos, &entityid, currColor, 1.f);
	}
}

void Killaura::onSendPacket(C_Packet* packet) {
	if (g_Data.isInGame()) {
		if (!g_Data.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
		targetListA = targetList.empty();
		targetList.clear();
		g_Data.forEachEntity(findEntity);
		struct CompareTargetEnArray {
			bool operator()(C_Entity* lhs, C_Entity* rhs) {
				C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
				return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
			}
		};
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
			if (!targetList.empty()) {
				auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				auto* authPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
				authPacket->pitch = angle.x;
				authPacket->yaw = angle.x;
				authPacket->yaw = angle.y;
			}
		}
	}
}