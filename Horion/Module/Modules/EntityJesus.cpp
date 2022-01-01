#include "EntityJesus.h"

#include "../../../Utils/Logger.h"

int EntityJesusChrist = 0;

EntityJesus::EntityJesus() : IModule(0, Category::ENTITY, "Walk over water, like EntityJesus") {
	//registerBoolSetting("Old EntityJesus", &walk, walk);
}

EntityJesus::~EntityJesus() {
}

const char* EntityJesus::getModuleName() {
	return "EntityJesus";
}

static std::vector<C_Entity*> getEntity;

void EntityJesusID(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 2118425 && currentEntity->getEntityTypeId() != 2118424)
		return;
	//2118423 is horse
	//2118425 is mule
	//2118424 is donkey

	//not worcking
	//2186010 is skeleton horse
	//Boat = 375

	int range = 4;
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < range) {
		getEntity.push_back(currentEntity);
	}
}

void EntityJesus::onMove(C_MoveInputHandler* input) {
	getEntity.clear();
	g_Data.forEachEntity(EntityJesusID);

	if (!getEntity.empty()) {
		auto player = getEntity[0];
		if (player == nullptr)
			return;

		if (player->isInLava() || player->isInWater())
			return;

		if (player->isSneaking())
			return;
	}
}

void EntityJesus::onWorldTick(C_GameMode* gm) {
	if (gm->player->isSneaking()) return;

	if (getEntity[0]->hasEnteredWater()) {
		getEntity[0]->velocity.y = 0.06f;
		getEntity[0]->onGround = true;
		wasInWater = true;
	} else if (getEntity[0]->isInWater() || getEntity[0]->isInLava()) {
		getEntity[0]->velocity.y = 0.1f;
		getEntity[0]->onGround = true;
		wasInWater = true;
	} else {
		if (wasInWater) {
			wasInWater = false;
			getEntity[0]->velocity.x *= 1.2f;
			getEntity[0]->velocity.x *= 1.2f;
		}
	}
	if (walk) return;
	{
		if (gm->player->isSneaking()) return;
		if (getEntity[0]->isOnFire()) return;

		vec3_t pos = *getEntity[0]->getPos();
		pos.y -= 1.62f;

		pos.z = getEntity[0]->aabb.upper.z;
		pos.x = getEntity[0]->aabb.upper.x;  // upper upper

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && getEntity[0]->velocity.y <= 0) {
			vec3_t pos = *getEntity[0]->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			getEntity[0]->setPos(pos);
			getEntity[0]->onGround = true;
			getEntity[0]->velocity.y = 0.f;
		}

		pos.x = getEntity[0]->aabb.lower.x;
		pos.z = getEntity[0]->aabb.lower.z;  // lower lower

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && getEntity[0]->velocity.y <= 0) {
			vec3_t pos = *getEntity[0]->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			getEntity[0]->setPos(pos);
			getEntity[0]->onGround = true;
			getEntity[0]->velocity.y = 0.f;
		}

		pos.x = getEntity[0]->aabb.upper.x;  // upper x and lower z
		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && getEntity[0]->velocity.y <= 0) {
			vec3_t pos = *getEntity[0]->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			getEntity[0]->setPos(pos);
			getEntity[0]->velocity.y = 0.f;
		}

		pos.x = getEntity[0]->aabb.lower.x;
		pos.z = getEntity[0]->aabb.upper.z;  // lower x and upper z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && getEntity[0]->velocity.y <= 0) {
			vec3_t pos = *getEntity[0]->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			getEntity[0]->setPos(pos);
			getEntity[0]->onGround = true;
			getEntity[0]->velocity.y = 0.f;
		}

		if (getEntity[0]->isInWater() || getEntity[0]->isInLava()) {
			getEntity[0]->velocity.y = 0.1f;
			getEntity[0]->onGround = true;
		}
	}
}