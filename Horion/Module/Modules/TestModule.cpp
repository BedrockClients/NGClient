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
#include "../../../SDK/CMobEffect.h"

using json = nlohmann::json;

TestModule::TestModule() : IModule(0, Category::WORLD, "For testing purposes") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("1", 1))
				.addEntry(EnumEntry("2", 2))
				.addEntry(EnumEntry("3", 3));

	registerFloatSetting("float1", &float1, 0, -10, 10);
	registerIntSetting("int1", &int1, 0, -10, 10);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("bool1", &bool1, true);
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

static void patchBytes(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void TestModule::onEnable() {
	if (targetAddress == nullptr)
		targetAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
	BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
	patchBytes((BYTE*)((uintptr_t)targetAddress), patch, 6);//FLUX SWING WOOOOOOOOOOOOOO
}

void TestModule::onTick(C_GameMode* gm) {
}

void TestModule::onMove(C_MoveInputHandler* hand) {
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(C_Packet* p) {
}

void TestModule::onDisable() {
	BYTE* patch = (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B\x46\x40\x48\x85\xC0";
	patchBytes((BYTE*)((uintptr_t)targetAddress), patch, 6);
}

void TestModule::onLevelRender() {
}