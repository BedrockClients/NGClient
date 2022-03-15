#include "CrystalAura.h"

CrystalAura::CrystalAura() : IModule(0x0, Category::COMBAT, "CrystalAura") {
	registerIntSetting("range", &range, range, 1, 10);
	registerBoolSetting("Multi", &doMultiple, doMultiple);
}
int crystalDelay = 0;
int crystalDelay2 = 0;
int crystalDelay3 = 0;

CrystalAura::~CrystalAura() {
}

const char* CrystalAura::getModuleName() {
	return ("CrystalAura");
}
static std::vector<C_Entity*> targetList7;

void findEntity3(C_Entity* currentEntity, bool isRegularEntity) {
	static auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();

	if (currentEntity == nullptr) return;
	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71) return; // crystal
	if (currentEntity == g_Data.getLocalPlayer()) return;  // Skip Local player
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) return;  // Don't hit this pesky antibot on 2b2e.org
	if (currentEntity->getEntityTypeId() == 64) return; // item
	if (currentEntity->getEntityTypeId() == 69) return; // xp_orb
	if (currentEntity->getEntityTypeId() == 80) return; // arrow
	if (!Target::isValidTarget(currentEntity)) return;
	//if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < CrystalAuraMod->range) {
		targetList7.push_back(currentEntity);
	}
}

bool checkTargCollision(vec3_t* block, C_Entity* ent) {
	std::vector<vec3_t*> corners;
	corners.clear();

	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z));
	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.lower.z));
	int n = 0;
	if (!corners.empty())
		for (auto corner : corners) {
			n++;

			if ((floor(corner->x) == floor(block->x)) && (floor(corner->y) == floor(block->y)) && (floor(corner->z) == floor(block->z))) {
				return true;
			}
		}

	return false;
}

bool checkSurrounded2(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;

	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();

	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1.f));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1.f));
		blockChecks.push_back(new vec3_ti(entPos.x + 1.f, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1.f, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		if (!checkTargCollision(&blocks->toVec3t(), ent)) {
			return false;
		}
	}
	return true;
}

std::vector<vec3_t*> getGucciPlacement2(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;
	std::vector<vec3_t*> finalBlocks;
	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();
	finalBlocks.clear();
	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1.f));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1.f));
		blockChecks.push_back(new vec3_ti(entPos.x + 1.f, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1.f, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		auto blkID = g_Data.getLocalPlayer()->region->getBlock(*blocks)->toLegacy()->blockId;
		auto blkIDL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 1, blocks->z))->toLegacy()->blockId;
		auto blkIDLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 2, blocks->z))->toLegacy()->blockId;
		auto blkIDLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 3, blocks->z))->toLegacy()->blockId;
		auto blkIDLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 4, blocks->z))->toLegacy()->blockId;

		if (!checkTargCollision(&blocks->toVec3t(), ent)) {  // very efficient coding here

			if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 1, blocks->z));
			} else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y, blocks->z));
			}
		} else {
			for (int x = entPos.x - 2; x <= entPos.x + 2; x++) {
				for (int z = entPos.z - 2; z <= entPos.z + 2; z++) {
					int y = entPos.y;
					auto blk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y, z))->toLegacy()->blockId;
					auto lBlk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y - 1, z))->toLegacy()->blockId;

					if ((blk == 0 && (lBlk == 49 || lBlk == 7))) {
						finalBlocks.push_back(new vec3_t(x, y, z));
					}
				}
			}
		}
	}
	return finalBlocks;
}

bool hasPlaced = false;
void CrystalAura::onEnable() {
	crystalDelay = 0;
	hasPlaced = false;
}
vec3_t espPosLower;
vec3_t espPosUpper;
vec3_t crystalPos;
std::vector<vec3_t*> placeArr;
std::vector<vec3_t*> hitArr;
void CrystalAura::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	if (g_Data.getLocalPlayer()->getSelectedItemId() == 259) return;

	targetList7.clear();

	g_Data.forEachEntity(findEntity3);
	hitArr.clear();
	placeArr.clear();

	if (g_Data.getLocalPlayer() != nullptr && !targetList7.empty())
		if ((crystalDelay >= delay) && !(targetList7.empty())) {
			crystalDelay = 0;
			if (!checkSurrounded2(targetList7[0])) {
				std::vector<vec3_t*> gucciPositions = getGucciPlacement2(targetList7[0]);

				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				auto inv = supplies->inventory;

				// 615 = normal id for crystal || 637 = crystal id for nukkit servers
				if (!gucciPositions.empty())
					if (g_Data.getLocalPlayer()->getSelectedItemId() == 637 || g_Data.getLocalPlayer()->getSelectedItemId() == 638) {
						placeArr.clear();
						for (auto place : gucciPositions) {
							if (hasPlaced && !doMultiple) break;
							if (targetList7.empty()) return;
							g_Data.getCGameMode()->buildBlock(&vec3_ti(place->x, place->y - 1.f, place->z), 1.f);
							placeArr.push_back(new vec3_t(place->x, place->y - 1, place->z));
							hasPlaced = true;
						}
					}

				gucciPositions.clear();
			}
		} else if (!targetList7.empty()) {
			crystalDelay++;
		}

	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		if (targetList7.empty()) return;
		int id = ent->getEntityTypeId();
		int range = moduleMgr->getModule<CrystalAura>()->range;
		if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
			g_Data.getCGameMode()->attack(ent);
			hasPlaced = false;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				g_Data.getLocalPlayer()->swingArm();
		}
	});
}

void CrystalAura::onPlayerTick(C_Player* plr) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (g_Data.getLocalPlayer()->getSelectedItemId() == 259) return;

	targetList7.clear();

	g_Data.forEachEntity(findEntity3);
	hitArr.clear();
	placeArr.clear();
}

void CrystalAura::onDisable() {
	crystalDelay = 0;
	hasPlaced = false;
}

void CrystalAura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		if (!placeArr.empty()) {
			for (auto postt : placeArr) {
				DrawUtils::setColor(1.0f, 0.0f, 0.0f, 1.f);
				DrawUtils::drawBox(postt->floor(), vec3_t(postt->x, postt->y, postt->z), 1.f, true);
			}
		}
	}
}