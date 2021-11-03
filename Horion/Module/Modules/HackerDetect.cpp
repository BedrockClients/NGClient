#include "HackerDetect.h"

HackerDetect::HackerDetect() : IModule(0, Category::MISC, "Detects Hackers") {
	registerFloatSetting("range", &range, range, 10.f, 100.f);
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

void findHackerman(C_Entity* currentEntity, bool isRegularEntity) {
	static auto hackerdetect = moduleMgr->getModule<HackerDetect>();

	if (currentEntity == nullptr)
		return;

	//if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
	//	return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < hackerdetect->range) {
		targetHackerman.push_back(currentEntity);
	}
}

void HackerDetect::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	targetHackerman.clear();
	g_Data.forEachEntity(findHackerman);

	if (!targetHackerman.empty()) {
		auto target = targetHackerman[0];
		vec3_t blockBelow = target->eyePos0;  // Block below the player
		blockBelow.y -= target->height;
		blockBelow.y -= 0.1f;
		auto speed = target->getSpeed();
		//clientMessageF("%f", speed);
		auto name = target->getNameTag()->getText();
		if (/*target->velocity.y == 0.0f && !target->onGround || */ target->velocity.x > 0.50f || target->velocity.z > 0.50f || target->velocity.y > 0.50f && !target->onGround || target->stepHeight > 0.6000f || player->region->getBlock(blockBelow)->blockLegacy->blockId == 30 && target->slowdownFactor == vec3_t(0, 0, 0) || target->isInWall()) {
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s is hacking", name);
		}
		if (counter == 2)
			counter++;
		else
			counter = 0;
	}
}

void HackerDetect::onSendPacket(C_Packet* packet) {
}