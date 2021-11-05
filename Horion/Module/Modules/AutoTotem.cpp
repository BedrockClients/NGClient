#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::COMBAT, "Automatically puts totems into your offhand") {
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("ForceTotem");
}

void AutoTotem::onLevelRender() {
	if (g_Data.getClientInstance()->isInGame()) {
		C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
		C_ItemStack* totem = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(0);
		C_InventoryAction* firstAction = nullptr;
		ItemDescriptor* desc = nullptr;
		C_ItemStack* yot = nullptr;
		int itemId = 0;
		if (g_Data.getLocalPlayer()->getEquippedTotem()->item == NULL) {
			if (totem->item != NULL && (*totem->item)->itemId == 449) {
				C_InventoryAction first(0, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
			if (itemId == 0) {
				TextHolder tempText("totem");
				std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
				std::unique_ptr<void*> buffer = std::make_unique<void*>();
				C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr.get(), buffer.get(), tempText);
				yot = new C_ItemStack(***cStack, 2, 0);
			}
			if (yot != nullptr)
				yot->count = 2;
			desc = new ItemDescriptor((*yot->item)->itemId, 0);
			firstAction = new C_InventoryAction(0, desc, nullptr, yot, nullptr, 2, 507, 99999);
			g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(*firstAction);
			delete firstAction;
			delete desc;
			g_Data.getLocalPlayer()->setOffhandSlot(yot);
			return;
		}
	}
}

void AutoTotem::onTick(C_GameMode* gm) {
	if (g_Data.getClientInstance()->isInGame()) {
		C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
		C_ItemStack* totem = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(0);
		C_InventoryAction* firstAction = nullptr;
		ItemDescriptor* desc = nullptr;
		C_ItemStack* yot = nullptr;
		int itemId = 0;
		if (g_Data.getLocalPlayer()->getEquippedTotem()->item == NULL) {
			if (totem->item != NULL && (*totem->item)->itemId == 449) {
				C_InventoryAction first(0, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
			if (itemId == 0) {
				TextHolder tempText("totem");
				std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
				std::unique_ptr<void*> buffer = std::make_unique<void*>();
				C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr.get(), buffer.get(), tempText);
				yot = new C_ItemStack(***cStack, 2, 0);
			}
			if (yot != nullptr)
				yot->count = 2;
			desc = new ItemDescriptor((*yot->item)->itemId, 0);
			firstAction = new C_InventoryAction(0, desc, nullptr, yot, nullptr, 2, 507, 99999);
			g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(*firstAction);
			delete firstAction;
			delete desc;
			g_Data.getLocalPlayer()->setOffhandSlot(yot);
			return;
		}
	}
}
