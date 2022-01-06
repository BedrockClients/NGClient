#pragma once
#include "Module.h"

class AutoPot : public IModule {
private:
	int health = 5;
	bool findPot() {
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
	bool isPot(C_ItemStack* itemStack) { return itemStack->getItem()->name.getText() == (std::string) "splash_potion"; }

public:
	AutoPot() : IModule(0, Category::COMBAT, "Auto throws potions at the selected health") {
		registerIntSetting("Health", &health, health, 1, 20);
		//registerIntSetting("Slot", &slot, slot, 1, 9);
	}
	~AutoPot(){}

	virtual void onSendPacket(C_Packet* packet) {
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->getHealth() <= health) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->pitch = 90;
		}
	}
	virtual void onTick(C_GameMode* gm) override {
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

				if (slot != 0) {
					inv->swapSlots(slot, potSlot);
				}
			}

			//checks if it can throw yet
			if (g_Data.getLocalPlayer()->getHealth() <= health) {
				findPot();
				Utils::rightClick();
			}
		}
	}
	const char* getModuleName() override { return "AutoPot"; }
};
