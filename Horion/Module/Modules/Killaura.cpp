#include "Killaura.h"

#include "../../../SDK/CAttribute.h"

void* targetAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 56 ? 48 85 D2 74 ? 48 8B 02");
Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	registerFloatSetting("range", &range, range, 2.f, 10.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerEnumSetting("Targeting", &targ, 2);
	targ = SettingEnum(this)
			   .addEntry(EnumEntry("Switch", 0))
			   .addEntry(EnumEntry("Multi", 1))
			   .addEntry(EnumEntry("Single", 2));
	registerBoolSetting("Info", &info, info);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerEnumSetting("Rotations", &rots, 3);
	rots = SettingEnum(this)
			   .addEntry(EnumEntry("Strafe", 0))
			   .addEntry(EnumEntry("Client", 1))
			   .addEntry(EnumEntry("Silent", 2))
			   .addEntry(EnumEntry("None", 3));
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerEnumSetting("BlockHit", &mode, 3);
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("SlideBlock", 0))
			   .addEntry(EnumEntry("SmoothBlock", 1))
			   .addEntry(EnumEntry("Normal", 2))
			   .addEntry(EnumEntry("None", 3));
	registerBoolSetting("NoSwing", &noSwing, noSwing);
}

Killaura::~Killaura() {
}

const char* Killaura::getModuleName() {
		return "Killaura";
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

//__int64 actualPlayerVTable = Utils::getBase() + 0x4195A10;

void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		static auto killauraMod = moduleMgr->getModule<Killaura>();

		if (currentEntity == nullptr || currentEntity == g_Data.getLocalPlayer() || !g_Data.getLocalPlayer()->canAttack(currentEntity, false) || !g_Data.getLocalPlayer()->isAlive() || !currentEntity->isAlive() || currentEntity->width <= 0.10f || currentEntity->height <= 0.10f)
			return;
		if (killauraMod->isMobAura) {
			if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
			if (currentEntity == nullptr) return;
			if (currentEntity == g_Data.getLocalPlayer()) return;// Skip Local player
			if (!currentEntity->isAlive()) return;
			if (!g_Data.getLocalPlayer()->isAlive()) return;
			if (currentEntity->getEntityTypeId() == 71) return;// endcrystal
			if (currentEntity->getEntityTypeId() == 66) return;// falling block
			if (currentEntity->getEntityTypeId() == 64) return;// item
			if (currentEntity->getEntityTypeId() == 69) return;// xp orb
			if (!Target::isValidTarget(currentEntity)) return;
		} else {
			if (!Target::isValidTarget(currentEntity)) return;
		}

		float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		if (dist < killauraMod->range) {
			targetList.push_back(currentEntity);
		}
	}
}

void Killaura::findWeapon() {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
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
float nigr = 0.f;
float nigr2 = 0.f;
int PlayerCount = 0;
void Killaura::onPlayerTick(C_Player* plr) {
	static auto prevTime = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> tDiff = now - prevTime;
	prevTime = now;
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);

		if (nigr >= 505)
			nigr = 340;
		else
			nigr += 2.f;

		if (nigr <= 339)
			nigr = 340;

		if (nigr2 >= 369)
			nigr2 = 340;
		else
			nigr2 += 1.5f;

		if (nigr2 <= 339)
			nigr2 = 340;

		if (!targetList.empty() && mode.selected == 0 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && !noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = nigr;
		} else if (!targetList.empty() && mode.selected == 1 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && !noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = nigr2;
		}
		targetList.clear();
		g_Data.forEachEntity(findEntity);
		if (!targetList.empty() && g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && rots.selected == 1) {
			vec2_t angle;
			if (targ.selected == 0)
				angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[PlayerCount]->getPos());
			else
				angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());

			plr->bodyYaw = angle.y;
			plr->yawUnused1 = angle.y;
			plr->pitch = angle.x;
		}
	}
}

void Killaura::onTick(C_GameMode* gm) {
	auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	targetListA = targetList.empty();
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		g_Data.forEachEntity(findEntity);
		if (autoweapon) findWeapon();
		if (!targetList.empty() && g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
			PlayerCount++;
			Odelay++;
			if (PlayerCount >= targetList.size())
				PlayerCount = 0;

			if (Odelay >= delay) {
				if (targ.selected == 1) {
					for (auto& i : targetList) {
						if (!(i->damageTime > 1 && hurttime)) {
							g_Data.getCGameMode()->attack(i);
							if (noSwing)
								return;
							gayFags = true;
							targethud++;
						} else {
							targethud = 0;
							counter = 0;
						}
					}
				} else if (targ.selected == 0) {
					if (!(targetList[0]->damageTime > 1 && hurttime)) {
						g_Data.getCGameMode()->attack(targetList[PlayerCount]);
						if (noSwing)
							return;
						gayFags = true;
						targethud++;
					} else {
						targethud = 0;
						counter = 0;
					}
				} else {
					if (!(targetList[0]->damageTime > 1 && hurttime)) {
						g_Data.getCGameMode()->attack(targetList[0]);
						if (noSwing)
							return;
						gayFags = true;
						targethud++;
					} else {
						targethud = 0;
						counter = 0;
					}
				}
				Odelay = 0;
			}
		}
	}
	if (targetList.empty()) {
		counter = 0;
		PlayerCount = 0;
	}

	if (!targetList.empty()) {
		if (mode.selected != 3 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon())
			Utils::nopBytes((BYTE*)targetAddress, 6);
		player->swing();
	}

	if (targetList.empty() && mode.selected != 3 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon()) {
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x84\x95\x02\x00\x00", 6);
		gayFags = false;
	}
}

void Killaura::onLevelRender() {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	targetListA = targetList.empty();
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		targetList.clear();
		g_Data.forEachEntity(findEntity);

		if (!targetList.empty()) {
			if (rots.selected == 0) {
				if (targ.selected == 0)
					joe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[PlayerCount]->getPos()).normAngles();
				else
					joe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				//player->bodyYaw = joe.x;
				//player->bodyYaw = joe.y;
			}
			int prevSlot;
			if (autoweapon) {
				findWeapon();
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
	srand(time(NULL));
	counter = 0;
	PlayerCount = 0;
	targetList.clear();
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}

void Killaura::onDisable() {
	Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x84\x95\x02\x00\x00", 6);
	gayFags = false;
	counter = 0;
	PlayerCount = 0;
	targetList.clear();
}

void Killaura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto partner = moduleMgr->getModule<Partner>();
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	if (g_Data.isInGame() && !targetList.empty() && info && g_Data.canUseMoveKeys && g_Data.getLocalPlayer()->canOpenContainerScreen() && targethud >= 1 && targetList[0]->isPlayer()) {
		//Atributes
		AbsorptionAttribute attribute = AbsorptionAttribute();
		HealthAttribute attribute2 = HealthAttribute();
		float Absorbtion = ((int)targetList[0]->getAttribute(&attribute)->currentValue);
		float Health = ((int)targetList[0]->getAttribute(&attribute2)->currentValue);
		float HealthMax = ((int)targetList[0]->getAttribute(&attribute2)->maximumValue);

		vec2_t res = g_Data.getClientInstance()->getGuiData()->windowSize;
		C_LocalPlayer* Player = g_Data.getClientInstance()->getLocalPlayer();
		if (Player != nullptr) {
			vec4_t rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) + (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 8.f));  // vec4_t rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) - (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 24.f));
			float rectWidth = rectPos.z - rectPos.x;

			//counter for fade
			counter++;
			if (counter == 100)
				counter--;

			//The actual box
			{
				DrawUtils::fillRectangle(vec4_t{rectPos.x - 1, rectPos.y - 1, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);

				// Gives the rounded corners effect
				if (partner->Partnered.selected == 0) {
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 1, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 2, rectPos.y - 1, rectPos.z + 2, rectPos.w + 1}, MC_Color(0, 0, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 2, rectPos.z + 1, rectPos.w + 2}, MC_Color(0, 0, 255), counter / 340.33333f);
				} else if (partner->Partnered.selected == 1) {
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 1, rectPos.z + 1, rectPos.w + 1}, MC_Color(150, 30, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 2, rectPos.y - 1, rectPos.z + 2, rectPos.w + 1}, MC_Color(150, 30, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 2, rectPos.z + 1, rectPos.w + 2}, MC_Color(150, 30, 255), counter / 340.33333f);
				} else if (partner->Partnered.selected == 2) {
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 1, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 2, rectPos.y - 1, rectPos.z + 2, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 2, rectPos.z + 1, rectPos.w + 2}, MC_Color(0, 255, 255), counter / 340.33333f);
				} else {
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 1, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 2, rectPos.y - 1, rectPos.z + 2, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				DrawUtils::drawRectangle(vec4_t{rectPos.x - 1, rectPos.y - 2, rectPos.z + 1, rectPos.w + 2}, MC_Color(0, 255, 255), counter / 340.33333f);
				}
			}

			//all the displays

			//Gets the targets name, then makes it not go to next line
			std::string targetName;
			auto Hud = moduleMgr->getModule<HudModule>();
			if (Hud->displaySecondHalf) {
				targetName = Utils::sanitize(targetList[0]->getNameTag()->getText());
				Utils::replaceString(targetName, '\n', ' ');
			} else {
				targetName = Utils::sanitize(targetList[0]->getNameTag()->getText());
				targetName = targetName.substr(0, targetName.find('\n'));
			}

			std::string healthString = std::to_string(((int)Health));
			std::string distance = "Distance: " + std::to_string((int)(*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
			std::string healthDisplay = "Health: " + healthString;
			std::string absorptionDisplay;

			//Absorbtion Bar
			if (Absorbtion > 0) {
				DrawUtils::drawRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + 1 * rectWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				std::string absorptionString = std::to_string((int)(Absorbtion));
				absorptionDisplay = "Absorption: " + absorptionString;
				float absorptionBarWidth = (Absorbtion / HealthMax) * rectWidth;
				if (!(targetList[0]->damageTime > 1))
					DrawUtils::fillRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				else
					DrawUtils::fillRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 0), counter / 100.f);
			}

			//The text
			{
				DrawUtils::drawText(vec2_t(rectPos.x + (res.x / 210.f), rectPos.y + (res.y / 550.f)), &targetName, MC_Color(255, 255, 255), 1.f, counter / 100.f);                 // name
				DrawUtils::drawText(vec2_t(rectPos.x + (res.x / 210.f), rectPos.y - 2 + (res.y / 35.f)), &healthDisplay, MC_Color(0, 255, 0), 0.7f, counter / 100.f);              // health
				DrawUtils::drawText(vec2_t(rectPos.x + 35 + (res.x / 210.f), rectPos.y - 2 + (res.y / 35.f)), &absorptionDisplay, MC_Color(255, 255, 85), 0.7f, counter / 100.f);  // absorbtion
				DrawUtils::drawText(vec2_t(rectPos.x + (res.x / 210.f), rectPos.y + 4 + (res.y / 35.f)), &distance, MC_Color(255, 255, 255), 0.7f, counter / 100.f);               // distance
			}
			DrawUtils::flush();

			//Health Bar
			{
				float healthBarWidth = (Health / HealthMax) * rectWidth;
				if (!(targetList[0]->damageTime > 1)) {
					DrawUtils::fillRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(0, 255, 0), counter / 100.f);
					DrawUtils::drawRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(0, 255, 0), counter / 100.f);
				} else {
					DrawUtils::fillRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
					DrawUtils::drawRectangle(vec4_t(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
				}
			}
			rectPos.y += res.y / 12.f;
			rectPos.w += res.y / 12.f;
		}

		DrawUtils::flush();
	}
}

void Killaura::onSendPacket(C_Packet* packet) {
	targetListA = targetList.empty();
	targetList.clear();
	g_Data.forEachEntity(findEntity);
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto BreakerMod = moduleMgr->getModule<Fucker>();
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && rots.selected == 1 || rots.selected == 2 && g_Data.isInGame() && !BreakerMod->destroy) {
		if (!targetList.empty()) {
			vec2_t angle;
			if (targ.selected == 0)
				angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[PlayerCount]->getPos());
			else
				angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());

			auto* pkt = reinterpret_cast<C_MovePlayerPacket*>(packet);
			float xChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.f));
			xChange -= 1.5f;

			pkt->yaw = angle.y + xChange;
			pkt->headYaw = angle.y + xChange;
			float yChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.5f));
			yChange -= 0.75f;
			pkt->pitch = angle.x + yChange;
		}
	}
}