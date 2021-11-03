#include "Spectator.h"

Spectator::Spectator() : IModule(0x0, Category::MISC, "Spectates Nearest Player") {
}

Spectator::~Spectator() {
}

const char* Spectator::getModuleName() {
	return ("Spectator");
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetList;

void findEntttttity(C_Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto SpectatorMod = moduleMgr->getModule<Spectator>();

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

	if (SpectatorMod->isMobAura) {
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
	if (dist < 200) {
		targetList.push_back(currentEntity);
	}
}

void Spectator::findWeapon() {
}

void Spectator::onTick(C_GameMode* gm) {
	if (g_Data.isInGame()) {
		if (!g_Data.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
		targetListA = targetList.empty();
		targetList.clear();
		g_Data.forEachEntity(findEntttttity);
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());

		Odelay++;
		if (!targetList.empty() && Odelay >= delay) {
			if (autoweapon) findWeapon();
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
			g_Data.getLocalPlayer()->currentPos.y = targetList[0]->currentPos.y + 2;
			g_Data.getLocalPlayer()->currentPos.x = targetList[0]->currentPos.x;
			g_Data.getLocalPlayer()->currentPos.z = targetList[0]->currentPos.z;
		}
		Odelay = 0;
	}
	if (!g_Data.isInGame()) {
		setEnabled(false);
	}
}

void Spectator::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}

void Spectator::onSendPacket(C_Packet* packet) {
	if (g_Data.isInGame()) {
		if (!g_Data.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
	}
}