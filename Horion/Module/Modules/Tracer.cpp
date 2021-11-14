#include "Tracer.h"
#include "../../../SDK/CCamera.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

Tracer::Tracer() : IModule('R', Category::VISUAL, "Draws lines to ESP highlighted entities") {
	registerEnumSetting("Tracer Type", &type, 0);
	type = SettingEnum(this)
			   .addEntry(EnumEntry("Normal Tracers", 0))
			   .addEntry(EnumEntry("Top Tracers", 1))
			   .addEntry(EnumEntry("Bottom tracers", 2));
	registerBoolSetting("Mob Tracers", &isMob, isMob);
	registerBoolSetting("Storage Tracers", &chest, chest);
	registerBoolSetting("RGB Tracers", &RGB, RGB);
	//registerBoolSetting("2D Tracers", &is2d, is2d);
	registerIntSetting("Red", &customR, customR, 0, 255);
	registerIntSetting("Green", &customG, customG, 0, 255);
	registerIntSetting("Blue", &customB, customB, 0, 255);
	//registerBoolSetting("Chests", &chest, chest);
	//registerIntSetting("Red", &customR2, customR2, 0, 255);
	//registerIntSetting("Green", &customG2, customG2, 0, 255);
	//registerIntSetting("Blue", &customB2, customB2, 0, 255);
}

Tracer::~Tracer() {
}

static float rcolors[4];

const char* Tracer::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (chest) {
			return "Tracers [Chest]";
		} else if (isMob) {
			return "Tracers [Mob]";
		} else if (RGB) {
			return "Tracers [RGB]";
		}
	} else
		return "Tracers";
}

void doRenderStuff3(C_Entity* ent, bool isRegularEntitie) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	static auto tracerMod = moduleMgr->getModule<Tracer>();
	static auto freecamMod = moduleMgr->getModule<Freecam>();
	if (ent == nullptr) return;

	vec3_t forwardVec = tracerMod->cameraPos;
	vec2_t facing = tracerMod->cameraRot;

	float calcYaw = (facing.y + 90) * (PI / 180);
	float calcPitch = (facing.x) * -(PI / 180);

	forwardVec.x += cos(calcYaw) * cos(calcPitch) * 0.2f;
	forwardVec.y += sin(calcPitch) * 0.2f;
	forwardVec.z += sin(calcYaw) * cos(calcPitch) * 0.2f;
	auto entPosition = ent->aabb.centerPoint();
	entPosition.y = ent->aabb.upper.y;

	if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
		DrawUtils::setColor(((float)tracerMod->customR / (float)255), ((float)tracerMod->customG / (float)255), ((float)tracerMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		DrawUtils::drawLine3d(forwardVec, entPosition);
	}
}

void Tracer::onLevelRender() {
	
}

void Tracer::onTick(C_GameMode* gm) {
	auto listLock = g_Data.lockChestList();
	auto* chestList = g_Data.getChestList();
	auto ourListLock = std::scoped_lock(this->listLock);

	this->bufferedChestList.clear();
	this->bufferedChestList.insert(this->bufferedChestList.end(), chestList->begin(), chestList->end());
}

void Tracer::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (!(is2d && g_Data.isInGame() && GameData::canUseMoveKeys()))
		return;

	if (isMob)
		g_Data.forEachEntity([](C_Entity* ent, bool valid) {
			DrawUtils::drawTracer(*ent->getPos(), ent->damageTime);
		});
	else
		g_Data.forEachEntity([](C_Entity* ent, bool valid) {
			if (Target::isValidTarget(ent) && ent != g_Data.getLocalPlayer())
				DrawUtils::drawTracer(*ent->getPos(), ent->damageTime);
		});
	if (chest) {
		for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter)
			DrawUtils::drawTracer(iter->get()->centerPoint());
	}
}