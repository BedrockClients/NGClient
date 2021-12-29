#include "InsideTP.h"
bool Behind;
float BehindLength;
float hoveringlength;
InsideTP::InsideTP() : IModule(0x0, Category::COMBAT, "TP Into The Closest Entity") {
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("UnlimitedRange", &unlim, unlim);
	registerFloatSetting("range", &range, range, 0.5f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerBoolSetting("Silent Rotations", &silent, silent);
	registerBoolSetting("Behind", &Behind, Behind);
	registerFloatSetting("BehindLength", &BehindLength, BehindLength, 0.1f, 5.f);
	registerFloatSetting("HoveringLength", &hoveringlength, hoveringlength, -5, 5);
}

InsideTP::~InsideTP() {}

const char* InsideTP::getModuleName() {
	return ("InsideAura");
}

static std::vector<C_Entity*> targetList;
void findEntity1(C_Entity* currentEntity, bool isRegularEntity) {
	static auto insideMod = moduleMgr->getModule<InsideTP>();

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

	if (insideMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (!insideMod->unlim) {
		if (dist < insideMod->range) {
			targetList.push_back(currentEntity);
		}
	} else {
		if (dist < 1000.f) {
			targetList.push_back(currentEntity);
		}
	}
}

void InsideTP::findWeapon() {
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

void InsideTP::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();
	g_Data.forEachEntity(findEntity1);

	Odelay++;
	vec3_t pos = *targetList[0]->getPos();
	float cy = (targetList[0]->yaw + 90) * (PI / 180);

	if (!targetList.empty()) {
		if (Odelay >= delay) {
			if (Behind) {
				pos.x -= cos(cy) * BehindLength;
				pos.z -= sin(cy) * BehindLength;
				pos.y += hoveringlength;
			}
			g_Data.getLocalPlayer()->setPos(pos);
			Odelay = 0;
		}
	}
}

void InsideTP::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void InsideTP::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
		if (!targetList.empty()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}