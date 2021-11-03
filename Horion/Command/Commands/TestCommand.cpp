#include "TestCommand.h"

#include <sstream>

#include "../../../SDK/Tag.h"
#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"

TestCommand::TestCommand() : IMCCommand("test", "Test for Debugging purposes", "") {
}

TestCommand::~TestCommand() {
}

void listEnts() {
	PointingStruct* pointingStruct = g_Data.getClientInstance()->getPointerStruct();
	auto entity = pointingStruct->getEntity();
	if (entity != nullptr) {
		int id = entity->getEntityTypeId();
		char* name = entity->getNameTag()->getText();
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Entity Name: %s", name);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Entity ID: %lld", id);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
	}
}

void itemId() {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto n = supplies->selectedHotbarSlot;
	C_ItemStack* stack = inv->getItemStack(n);
	if (stack->item != nullptr) {
		auto id = stack->getItem()->itemId;
		char* name = stack->getItem()->name.getText();
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Item Name: %s", name);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Item ID: %lld", id);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
	}
}

void showAimedBlockInfo() {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	PointingStruct* pointingStruct = g_Data.getClientInstance()->getPointerStruct();
	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointingStruct->block);
	auto entity = pointingStruct->getEntity();
	if (block != nullptr && pointingStruct != nullptr && entity == nullptr && block->blockLegacy->blockId != 7) {
		char* name = block->toLegacy()->name.getText();
		auto id = block->toLegacy()->blockId;
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Block Name: %s", name);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("Block ID: %lld", id);
		g_Data.getClientInstance()->getGuiData()->displayClientMessageF("---------------");
	}
}

bool TestCommand::execute(std::vector<std::string>* args) {
	listEnts();
	itemId();
	showAimedBlockInfo();
	return true;
}