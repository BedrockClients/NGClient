#include "ChestStealer.h"

#include "../ModuleManager.h"

ChestStealer::ChestStealer() : IModule(0, Category::PLAYER, "Automatically takes or dumps all items out of a chest or into a chest") {
	registerIntSetting("Close Delay", &this->setDelay, this->setDelay, 0, 20);
	registerBoolSetting("enhanced", &this->enhanced, this->enhanced);
	registerBoolSetting("dump", &this->dump, this->dump);
}

ChestStealer::~ChestStealer() {
}

const char* ChestStealer::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (enhanced) {
			return "ChestStealer [Enhanced]";
		} else
			return "ChestStealer";
	} else
		return "ChestStealer";
}

void ChestStealer::chestScreenController_tick(C_ChestScreenController* c) {
	if (dump) {
		if (c != nullptr) {
			std::vector<int> items = {};
			auto invcleanerMod = moduleMgr->getModule<InventoryCleaner>();
			for (int i = 0; i < 54; i++) {
				C_ItemStack* stack = c->_getItemStack(TextHolder("inventory_items"), i);
				C_ItemStack* stack2 = c->_getItemStack(TextHolder("hotbar_items"), i);
				if (stack != nullptr && stack->item != NULL || stack2 != nullptr && stack2->item != NULL)
					if (!this->enhanced || invcleanerMod->stackIsUseful(stack) || invcleanerMod->stackIsUseful(stack))
						items.push_back(i);
			}
			if (!items.empty()) {
				for (int i : items) {
					c->handleAutoPlace(0x7FFFFFFF, "inventory_items", i);
					c->handleAutoPlace(0x7FFFFFFF, "hotbar_items", i);
				}
			} else {
				delay++;
				if (delay > setDelay) {
					c->tryExit();
					delay = 0;
				}
			}
		}
	} else {
		if (c != nullptr) {
			std::vector<int> items = {};
			auto invcleanerMod = moduleMgr->getModule<InventoryCleaner>();
			for (int i = 0; i < 54; i++) {
				C_ItemStack* stack = c->_getItemStack(TextHolder("container_items"), i);
				if (stack != nullptr && stack->item != NULL)
					if (!this->enhanced || invcleanerMod->stackIsUseful(stack))
						items.push_back(i);
			}
			if (!items.empty()) {
				for (int i : items) {
					c->handleAutoPlace(0x7FFFFFFF, "container_items", i);
				}
			} else {
				delay++;
				if (delay > setDelay) {
					c->tryExit();
					delay = 0;
				}
			}
		}
	}
}