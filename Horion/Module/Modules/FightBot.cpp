#include "FightBot.h"

FightBot::FightBot() : IModule(0, Category::COMBAT, "Moves and attacks at the closest player") {
	registerFloatSetting("Range", &range, range, 3.f, 1000.f);
	registerFloatSetting("Reach", &reach, reach, 2.f, 7.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hurttime", &hurttime, hurttime);
}

FightBot::~FightBot() {
}

const char* FightBot::getModuleName() {
	return ("FightBot");
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};
static std::vector<C_Entity*> targetList;

void finnndEntity(C_Entity* currentEntity, bool isRegularEntity) {
	struct CompareTargetEnArray {
		bool operator()(C_Entity* lhs, C_Entity* rhs) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto killauraMod = moduleMgr->getModule<FightBot>();

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

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void FightBot::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	targetList.clear();
	g_Data.forEachEntity(finnndEntity);
	struct CompareTargetEnArray {
		bool operator()(C_Entity* lhs, C_Entity* rhs) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
		}
	};
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		if (!(targetList[0]->damageTime > 1 && hurttime)) {
			//	g_Data.getLocalPlayer()->swing();
			//	g_Data.getCGameMode()->attack(targetList[0]);
		}
		auto player = g_Data.getLocalPlayer();
		vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
		player->bodyYaw = angle.x;
		player->bodyYaw = angle.y;
		bot = angle;
		g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
		g_Data.getClientInstance()->localPlayer->setSprinting(true);
	}
}

void FightBot::onDisable() {
	targetList.clear();
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	g_Data.getClientInstance()->localPlayer->setSprinting(false);
}