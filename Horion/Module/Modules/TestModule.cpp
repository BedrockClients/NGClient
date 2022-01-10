#include "TestModule.h"

TestModule::TestModule() : IModule(0, Category::WORLD, "For testing purposes") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("1", 1))
				.addEntry(EnumEntry("2", 2))
				.addEntry(EnumEntry("3", 3));

	registerFloatSetting("float1", &float1, 0, -10, 10);
	registerIntSetting("Sound", &int1, int1, 0, 500);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("Random", &bool1, true);
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
	//static std::vector<vec3_t> uwu;
	//	uwu.push_back(vec3_t(10, 17, 10));
	//vec3_t calc = uwu.sub(*current);
}

void TestModule::onTick(C_GameMode* gm) {
	//gm->player->pitch = 0;
	//gm->player->bodyYaw = 90;
	//gm->player->yawUnused1 = 90;
}

void TestModule::onMove(C_MoveInputHandler* hand) {
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(C_Packet* packet) {
}

void TestModule::onDisable() {
//	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
}

void TestModule::onLevelRender() {
}

void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	//C_TexturePtr texture;
	//texture.filePath = TextHolder("texture/ui/hotbar_2");
	//__int64 yot = 0;
	//DrawUtils::drawImage("texture/ui/hotbar_2", vec2_t(100, 100), vec2_t(100, 300), vec2_t(1, 1));
	//renderCtx->drawImage(&texture, vec2_t(100, 100), vec2_t(500, 100), yot, vec2_t(1, 1));
}