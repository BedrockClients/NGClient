#include "TestModule.h"

#include <array>
#include <deque>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_transform.hpp>  // perspective, translate, rotate
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>  //radians
#include <unordered_set>

#include "../../../SDK/MatrixStack.h"
#include "../../../Utils/Json.hpp"
#include "../../../Utils/Logger.h"
#include "../../../Utils/VoxelIntersector.h"
#include "../../DrawUtils.h"
#include "../../path/JoeMovementController.h"
#include "../../path/JoePathFinder.h"
#include "../../path/goals/JoeGoal.h"
#include "../../path/goals/JoeGoalXZ.h"

using json = nlohmann::json;

TestModule::TestModule() : IModule(0, Category::WORLD, "For testing purposes") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("1", 1))
				.addEntry(EnumEntry("2", 2))
				.addEntry(EnumEntry("3", 3));

	registerFloatSetting("float1", &this->float1, 0, -10, 10);
	registerIntSetting("int1", &this->int1, 0, -10, 10);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("bool1", &this->bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

static std::vector<C_Entity*> tagtr;
void findjeoe(C_Entity* currentEntity, bool isRegularEntitie) {
	static auto test = moduleMgr->getModule<TestModule>();

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

	if (currentEntity->getEntityTypeId() != 63)
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < 100) {
		tagtr.push_back(currentEntity);
	}
}

void TestModule::onEnable() {
	if (g_Data.isInGame()) {
		auto freecam = moduleMgr->getModule<Freecam>();
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec3_ti block = g_Data.getClientInstance()->getPointerStruct()->block;
		if (block == vec3_ti(0, 0, 0)) return;
		vec3_t pos = block.toVec3t();
		pos.y += 1.5f;

		vec3_t tpPos = pos;

		player->vehicleLanded(tpPos, tpPos);
		//tpPos.y += (player->getPos()->y - player->getAABB()->lower.y) + 1;  // eye height + 1
		//player->startSleepInBed(tpPos) /* ? 0 : 100;*/;
		//freecam->setEnabled(true);
		//player->stopSleepInBed(false, false) /* ? 0 : 100;*/;
		//freecam->setEnabled(false);
		//freecam->setEnabled(true);
		//freecam->setEnabled(false);
		//setEnabled(false);
	}
}

void TestModule::onTick(C_GameMode* gm) {
	if (g_Data.isInGame()) {
		vec3_ti block = g_Data.getClientInstance()->getPointerStruct()->block;
		if (block == vec3_ti(0, 0, 0)) return;
		vec3_t pos = block.toVec3t();
		pos.y += 1.5f;

		vec3_t tpPos = pos;
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->doFireHurt(1);
	}
}

void TestModule::onMove(C_MoveInputHandler* hand) {
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(C_Packet* p) {
}

void TestModule::onDisable() {
}

void TestModule::onLevelRender() {
}