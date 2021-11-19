#include "ChestStealer.h"

#include "../ModuleManager.h"

ChestStealer::ChestStealer() : IModule(0, Category::PLAYER, "Automatically takes all items out of a chest") {
	registerIntSetting("Close Delay", &this->setDelay, this->setDelay, 0, 20);
	registerBoolSetting("enhanced", &this->enhanced, this->enhanced);
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