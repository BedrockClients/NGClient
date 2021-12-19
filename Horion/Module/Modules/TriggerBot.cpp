#include "TriggerBot.h"

#include "../../../Utils/Target.h"

TriggerBot::TriggerBot() : IModule(0, Category::COMBAT, "Attacks entities you're looking at") {
	registerIntSetting("delay", &delay, delay, 0, 20);
}

TriggerBot::~TriggerBot() {
}

const char* TriggerBot::getModuleName() {
	return ("TriggerBot");
}
void TriggerBot::onEnable() {
	C_Entity* target = g_Data.getClientInstance()->getPointerStruct()->getEntity();
	if (!Target::isValidTarget(target))
		return;
}

void TriggerBot::onDisable() {
	C_Entity* target = g_Data.getClientInstance()->getPointerStruct()->getEntity();
	if (!Target::isValidTarget(target))
		return;
}
void TriggerBot::onTick(C_GameMode* gm) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	C_Entity* target = g_Data.getClientInstance()->getPointerStruct()->getEntity();
	
	Odelay++;
	if (target > 0 && Odelay >= delay) {

		localPlayer->swingArm();
		gm->attack(target);

		Odelay = 0;
	}
}
