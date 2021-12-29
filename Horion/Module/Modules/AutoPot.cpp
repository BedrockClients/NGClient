#include "AutoPot.h"
#include "../../../Memory/Hooks.h"
//int slot = 0;
AutoPot::AutoPot() : IModule(0, Category::COMBAT, "Auto throws potions at the selected health") {
	registerIntSetting("Health", &health, health, 1, 20);
	//registerIntSetting("Slot", &slot, slot, 1, 9);
}
AutoPot::~AutoPot() {
}

const char* AutoPot::getModuleName() {
	return "AutoPot";
}

bool AutoPot::findPot() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (isPot(stack)) {
				if (prevSlot != n) {
					supplies->selectedHotbarSlot = n;
					C_MobEquipmentPacket p;
					p.hotbarSlot = n;
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
				}
				return true;
			}
		}
	}
	return false;
}

bool AutoPot::isPot(C_ItemStack* itemStack) {
	return itemStack->getItem()->name.getText() == (std::string)"splash_potion";
}

void AutoPot::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	if (g_Data.getLocalPlayer()->isAlive() && g_Data.isInGame()) {
		//Put Pots in Horbar But not working for some reason
		if (!g_Data.getLocalPlayer()->canOpenContainerScreen()) {
			int slot;
			int potSlot;
			for (int n = 0; n < 36; n++) {
				C_ItemStack* stack = inv->getItemStack(n);
				if (stack->item != nullptr && isPot(stack)) {
					auto PotSlot = inv->getFirstEmptySlot();
					potSlot = PotSlot;
					slot = n;
				}
			}

			int from = potSlot;
			int to = slot;
			if (to != from) {
				C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
				C_ItemStack* i1 = inv->getItemStack(from);
				C_ItemStack* i2 = inv->getItemStack(to);
				C_InventoryAction first(from, i1, nullptr);
				C_InventoryAction second(to, i2, i1);
				C_InventoryAction third(from, nullptr, i2);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
				manager->addInventoryAction(third);
			}
		}

		//checks if it can throw yet
		if (g_Data.getLocalPlayer()->getHealth() <= health) {
			findPot();
			Utils::rightClick();
		}
	}
}

void AutoPot::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->getHealth() <= health) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->pitch = 90;
	}
}
