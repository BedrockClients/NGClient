#include "HackerDetect.h"

HackerDetect::HackerDetect() : IModule(0, Category::SERVER, "Detects Hackers") {
}

HackerDetect::~HackerDetect() {
}

const char* HackerDetect::getModuleName() {
	return "HackerDetect";
}

static std::vector<C_Entity*> targetHackerman;
struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

__int64 theVTableOfAnEntityThatIsProbablyActuallyAPlayerAndNotSomeRandomFuckingThingThatMakesYouCrash = Utils::getBase() + 0x3E403A0;

void findHackerman(C_Entity* currentEntity, bool isRegularEntity) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
		static auto hackerdetect = moduleMgr->getModule<HackerDetect>();

		__int64 avc = reinterpret_cast<__int64>(currentEntity);

		if (currentEntity == nullptr || avc < 0x10000000000 || avc > 0x100000000000 || *(__int64*)currentEntity != theVTableOfAnEntityThatIsProbablyActuallyAPlayerAndNotSomeRandomFuckingThingThatMakesYouCrash)
			return;

		if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
			return;

		if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
			return;

		if (!g_Data.getLocalPlayer()->isAlive())
			return;

		if (!currentEntity->isAlive())
			return;

		if (!currentEntity->isPlayer())
			return;
		if (!currentEntity->isValidTarget(currentEntity))
			return;

		float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		if (dist < 1000) {
			targetHackerman.push_back(currentEntity);
		}
	}
}

void HackerDetect::onTick(C_GameMode* gm) {
	targetHackerman.clear();
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->pointingStruct->getLevelTicks() > 50) {
		g_Data.forEachEntity(findHackerman);
		if (targetHackerman.size() < 1) return;
		auto target = targetHackerman[0];
		auto speed = target->getRealSpeed();
		auto name = target->getNameTag()->getText();
		if (target->stepHeight > 0.6000f || target->isInWall() || target->isImmobile() && target->getBlocksPerSecond() > 1.f || target->getBlocksPerSecond() > 12.f) {
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s is hacking", name);
		}
	}
}

void HackerDetect::onSendPacket(C_Packet* packet) {
}