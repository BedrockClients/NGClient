#include "InsideTP.h"

InsideTP::InsideTP() : IModule(0x0, Category::COMBAT, "TP Into The Closest Entity") {
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("UnlimitedRange", &unlim, unlim);
	registerBoolSetting("PushMode", &pushm, pushm);
	registerFloatSetting("range", &range, range, 0.5f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerBoolSetting("Silent Rotations", &silent, silent);
}

InsideTP::~InsideTP() {
}

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
		if (dist < insideMod->unlimRange) {
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
	if (!targetList.empty() && Odelay >= delay) {
		vec3_t pos = *targetList[0]->getPos();
		if (autoweapon) findWeapon();
		if (!pushm) {
			//if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			//}
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			player->setPos(pos);
		} else {
			float dist2 = gm->player->getPos()->dist(pos);
			g_Data.getLocalPlayer()->setPos(pos);  // lerpTo gone   , vec2_t(1, 1), (int)fmax((int)dist2 * 0.1, 1));
		}
		Odelay = 0;
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