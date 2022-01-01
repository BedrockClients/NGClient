#include "EntitySpeed.h"

EntitySpeed::EntitySpeed() : IModule(0, Category::ENTITY, "Increases your speed within boats") {
	registerFloatSetting("Speed", &speed, speed, 1.f, 10.f);
}

EntitySpeed::~EntitySpeed() {
}

const char* EntitySpeed::getModuleName() {
	return ("EntitySpeed");
}

static std::vector<C_Entity*> targetList;

void getEntityId(C_Entity* currentEntity, bool isRegularEntity) {
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

	int range = 3;
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < range) {
		targetList.push_back(currentEntity);
	}
}

void EntitySpeed::onWorldTick(C_GameMode* gm) {
	targetList.clear();
	g_Data.forEachEntity(getEntityId);

	if (!targetList.empty()) {
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
			moveVec.y = targetList[0]->velocity.y;
			moveVec.z = sin(calcYaw) * speed;
			if (keyPressed) {
				targetList[0]->lerpMotion(moveVec);
				keyPressed = false;
			}
		}
	}
}