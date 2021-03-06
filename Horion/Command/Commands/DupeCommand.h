#pragma once
#include "ICommand.h"

class DupeCommand : public IMCCommand {
public:
	DupeCommand() : IMCCommand("dupe", "Duplicates the item in hand", "<count> <mode: give / offhand : 1/0>") {}
	~DupeCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
		int selectedSlot = supplies->selectedHotbarSlot;
		C_ItemStack* item = inv->getItemStack(selectedSlot);
		int count = item->count;
		bool isGive = true;
		if (args->size() > 1)
			item->count = assertInt(args->at(1));
		if (args->size() > 2)
			isGive = static_cast<bool>(assertInt(args->at(2)));
		if (isGive) {
			int slot = inv->getFirstEmptySlot();
			C_InventoryAction* firstAction = nullptr;
			C_InventoryAction* secondAction = nullptr;

			firstAction = new C_InventoryAction(0, item, nullptr, 507, 99999);

			transactionManager->addInventoryAction(*firstAction);

			inv->addItemToFirstEmptySlot(item);
		} else
			g_Data.getLocalPlayer()->setOffhandSlot(item);
		if (args->size() > 1)
			item->count = count;
		clientMessageF("%sSuccessfully duplicated the item!", LIGHT_PURPLE);
		return true;
	}
};