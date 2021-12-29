#include "AutoPot.h"
int slot = 0;
AutoPot::AutoPot() : IModule(0, Category::COMBAT, "Auto throws potions at the selected health") {
	registerIntSetting("Health", &health, health, 1, 20);
	registerIntSetting("Slot", &slot, slot, 1, 9);
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
	if (g_Data.getLocalPlayer()->isAlive() && g_Data.isInGame()) {
		//Put Pots in Horbar
		if (!g_Data.getLocalPlayer()->canOpenContainerScreen()) {
			C_Inventory* inv = supplies->inventory;
			for (int n = 0; n < 36; n++) {
				C_ItemStack* stack = inv->getItemStack(n);
				if (stack->item != nullptr) {
					if (isPot(stack)) {
							if (n != 5) inv->moveItem(n, 5);
					}
				}
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
