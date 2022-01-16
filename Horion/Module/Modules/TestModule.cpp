#include "TestModule.h"
#include "../../../Memory/Hooks.h"

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
}

void TestModule::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	//plr->pitch = 0;
	//plr->bodyYaw = 90;
	//plr->yawUnused1 = 90;
}

void TestModule::onTick(C_GameMode* gm) {
}

void TestModule::onWorldTick(C_GameMode* gm) {
}

void TestModule::onMove(C_MoveInputHandler* hand) {
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(C_Packet* packet) {
}

void TestModule::onDisable() {
	CommandRequestPacket mpp("/q sky");
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
}

void TestModule::onLevelRender() {
}

void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	//std::string screenName(g_Hooks.currentScreenName);
	//if (screenName != "toast_screen" && screenName != "start_screen" && screenName != "debug_screen" && screenName != "pause_screen" && screenName != "�$0a-" && screenName != "�A&w-")
	//DrawUtils::drawText(vec2_t{100, 100}, &screenName, MC_Color(0, 0, 255));

	//C_TexturePtr texture;
	//texture.filePath = TextHolder("texture/ui/hotbar_2");
	//__int64 yot = 0;
	//DrawUtils::drawImage("texture/ui/hotbar_2", vec2_t(100, 100), vec2_t(100, 300), vec2_t(1, 1));
	//renderCtx->drawImage(&texture, vec2_t(100, 100), vec2_t(500, 100), yot, vec2_t(1, 1));
}