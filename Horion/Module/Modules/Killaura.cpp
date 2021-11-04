#include "Killaura.h"

Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	registerBoolSetting("Info", &info, info);
	registerBoolSetting("TargetHud", &targethud, targethud);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerFloatSetting("range", &range, range, 2.f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
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
		targetList.clear();
		g_Data.forEachEntity(findEntity);

		if (!targetList.empty()) {
			Odelay++;
			if (!targetList.empty() && Odelay >= delay) {
				if (autoweapon) findWeapon();
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
				if (rotations) {
					vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
					auto player = g_Data.getLocalPlayer();
					player->lookAt(player, angle.x, angle.y);
				}
				Odelay = 0;
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
				player->yawUnused2 = angle.x;
				player->yawUnused2 = angle.y;
				player->bodyYaw = angle.x;
				player->bodyYaw = angle.y;
			}
			if (rotations) {
				auto player = g_Data.getLocalPlayer();
				vec3_t origin = g_Data.getLocalPlayer()->eyePos0;  // TODO: sort list
				C_Entity* entity = targetList[0];
				vec3_t pos = entity->aabb.centerPoint();
				pos = pos.sub(origin);
				float yaw = (atan2f(pos.z, pos.x) * DEG_RAD) - 90;
				float len = pos.magnitudexz();
				constexpr float g = 0.002f;  // nukkit = 0.012, some servers need different values
				float tmp = 1 - g * (g * (len * len) + 2 * pos.y);
				float pitch = DEG_RAD * -atanf((1 - sqrtf(tmp)) / (g * len));
				vec2_t angle;
				angle = vec2_t(pitch, yaw);
				auto movePacket = g_Data.getLocalPlayer();
				player->bodyYaw = angle.y;
				player->yaw = angle.y;
				player->viewAngles = angle;
				movePacket->yawUnused1 = angle.y;
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
				return;
			}
		}
	}
	if (!g_Data.isInGame())
		setEnabled(false);
}

void Killaura::onEnable() {
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
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

void Killaura::onPostRender(C_MinecraftUIRenderContext* ctx) {
	static auto Info = moduleMgr->getModule<Killaura>();

	static auto Killauramod = moduleMgr->getModule<Killaura>();
	if (!targetList.empty() && g_Data.isInGame()) {
		vec4_t tempPos = vec4_t(/*y*/ 170.f, /*z*/ 325.f, /*?*/ 90.f, /*?*/ 40.f);  // text temp pos for the text pos, so we can create a pos that doesn't have player names overlapping from the box to the screen
		vec2_t textPos = vec2_t(tempPos.y, tempPos.x);                              //text pos
		static float rcolors2[4];                                                   // Rainbow color array RGBA
		static float disabledRcolors2[4];                                           // Rainbow Colors, but for disabled modules
		static float currColor[4];                                                  // ArrayList colors

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
		std::string name = targetList[0]->getNameTag()->getText();
		std::string distance = "Distance: " + std::to_string((*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
		std::string X = "X: " + std::to_string((targetList[0]->getPos()->x));
		std::string Y = "Y: " + std::to_string((targetList[0]->getPos()->y));
		std::string Z = "Z: " + std::to_string((targetList[0]->getPos()->z));

		DrawUtils::drawText(textPos, &name, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &distance, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &X, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &Y, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &Z, currColor, 1.f);

		if (Info->info) {
			static auto Killauramod = moduleMgr->getModule<Killaura>();
			if (!targetList.empty() && g_Data.isInGame()) {
				vec4_t tempPos = vec4_t(120.f, 5.f, 90.f, 40.f);           //temp pos for the text pos, so we can create a pos that doesn't have player names overlapping from the box to the screen
				vec2_t textPos = vec2_t(tempPos.y, tempPos.x);             //text pos
				vec4_t pos = vec4_t(3.f, 118.f, 75.f + textPos.x, 233.f);  //pos for using
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
				std::string name = targetList[0]->getNameTag()->getText();
				std::string distance = "Distance: " + std::to_string((*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
				std::string X = "X: " + std::to_string((targetList[0]->getPos()->x));
				std::string Y = "Y: " + std::to_string((targetList[0]->getPos()->y));
				std::string Z = "Z: " + std::to_string((targetList[0]->getPos()->z));
				std::string DmgTime = "DmgTime: " + std::to_string((targetList[0]->damageTime));
				std::string OnGround = "OnGround: " + std::to_string((targetList[0]->onGround));
				std::string height = "height: " + std::to_string((targetList[0]->height));
				std::string entityid = "EntityID: " + std::to_string((targetList[0]->getEntityTypeId()));
				DrawUtils::drawRectangle(pos, currColor, 1.f);
				DrawUtils::fillRectangle(pos, MC_Color(00, 00, 00), 1.0f);
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
	}
}
