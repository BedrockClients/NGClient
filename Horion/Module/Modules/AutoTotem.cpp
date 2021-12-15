#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::COMBAT, "Automatically puts totems into your offhand") {
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("ForceTotem");
}

void AutoTotem::onLevelRender() {
	if (g_Data.getClientInstance()->isInGame() && g_Data.getLocalPlayer()->getEquippedTotem()->getItem()->itemId != 568) {
		C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("totem")), 1, 0);
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->setOffhandSlot(yot);
	}
}

void AutoTotem::onTick(C_GameMode* gm) {
	if (g_Data.getClientInstance()->isInGame() && g_Data.getLocalPlayer()->getEquippedTotem()->getItem()->itemId != 568) {
		C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("totem")), 1, 0);
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->setOffhandSlot(yot);
	}
}
