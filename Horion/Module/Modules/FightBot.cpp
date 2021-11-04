#include "FightBot.h"

FightBot::FightBot() : IModule(0, Category::COMBAT, "Bot For PVP") {
	registerFloatSetting("Range", &range, range, 3.f, 1000.f);
	registerFloatSetting("Hit Range", &reach, reach, 2.f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
}

FightBot::~FightBot() {
}

const char* FightBot::getModuleName() {
	return ("FightBot");
}

static std::vector<C_Entity*> targetList;

void findEeentity(C_Entity* currentEntity, bool isRegularEntity) {
	struct CompareTargetEnArray {
		bool operator()(C_Entity* lhs, C_Entity* rhs) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto FightBotMod = moduleMgr->getModule<FightBot>();

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

	if (FightBotMod->isMobAura) {
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
	if (dist < FightBotMod->range) {
		targetList.push_back(currentEntity);
	}
}

void FightBot::findWeapon() {
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

void FightBot::onTick(C_GameMode* gm) {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	targetListA = targetList.empty();
	targetList.clear();
	g_Data.forEachEntity(findEeentity);
	struct CompareTargetEnArray {
		bool operator()(C_Entity* lhs, C_Entity* rhs) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
		g_Data.getClientInstance()->localPlayer->setSprinting(true);
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
		if (sexy) {
			vec2_t anglee = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
			bot = anglee;
			auto player = g_Data.getLocalPlayer();
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
			player->yawUnused2 = angle.x;
			player->yawUnused2 = angle.y;
			player->bodyYaw = angle.x;
			player->bodyYaw = angle.y;
		}
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

void FightBot::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void FightBot::onDisable() {
	targetList.clear();
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	g_Data.getClientInstance()->localPlayer->setSprinting(false);
}

void FightBot::onSendPacket(C_Packet* packet) {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	targetListA = targetList.empty();
	targetList.clear();
}