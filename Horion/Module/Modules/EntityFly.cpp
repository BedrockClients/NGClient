#include "../ModuleManager.h"
#include "EntityFly.h"

EntityFly::EntityFly() : IModule(0, Category::ENTITY, "Fly, for entitys (Use arrow Keys for Virtical Movement!)") {
	registerFloatSetting("Fly Speed", &speed, speed, 1.f, 10.f);
}

EntityFly::~EntityFly() {
}

const char* EntityFly::getModuleName() {
	return ("EntityFly");
}

static std::vector<C_Entity*> targetList;

void findBooat(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 2118425 && currentEntity->getEntityTypeId() != 2118424 && currentEntity->getEntityTypeId() != 2186010)
		return;
	//2118423 is horse
	//2118425 is mule
	//2118424 is donkey
	//2186010 is skeleton horse
	float boatdistance = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (boatdistance < 3) {
		targetList.push_back(currentEntity);
	}
}

void EntityFly::onTick(C_GameMode* gm) {
	targetList.clear();
	g_Data.forEachEntity(findBooat);

	if (!targetList.empty()) {
		float boatdistance = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

		if (boatdistance < 3) {
			gm->player->onGround;
			float yaw = gm->player->yaw;
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			bool keyPressed = false;
			if (GameData::canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
				return;
			else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				yaw += 45.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				yaw -= 45.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				yaw += 135.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				yaw -= 135.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->forwardKey)) {
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->backKey)) {
				yaw += 180.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				yaw += 90.f;
				keyPressed = true;
			} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				yaw -= 90.f;
				keyPressed = true;
			}
			float calcYaw = (yaw + 90) * (PI / 180);
			float calcPitch = (gm->player->pitch) * -(PI / 180);
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.y = targetList[0]->velocity.y = 0;
			moveVec.z = sin(calcYaw) * speed;
			if (keyPressed) {
				targetList[0]->lerpMotion(moveVec);
				keyPressed = false;
			} else {
				targetList[0]->velocity.x = 0;
				targetList[0]->velocity.z = 0;
			}
			//up and down
			if (g_Data.canUseMoveKeys() && !targetList.empty()) {
				if (GameData::isKeyDown(VK_DOWN)) {
					targetList[0]->velocity.y -= speed;
				}
				if (GameData::isKeyDown(VK_UP)) {
					targetList[0]->velocity.y += speed;
				}
			}
			}
		}
	}
}