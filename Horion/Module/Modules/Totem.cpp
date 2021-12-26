#include "Totem.h"

Totem::Totem() : IModule(0, Category::COMBAT, "Automatically puts totems from your inventory into your offhand") {
}

Totem::~Totem() {
}

const char* Totem::getModuleName() {
	return ("AutoTotem");
}

void Totem::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
	if (current->item == NULL) {
		for (int i = 0; i < 36; i++) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == 568) {
				C_InventoryAction first(i, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
		}
	}
}