#pragma once
#include "ICommand.h"
class EnchantCommand : public IMCCommand {
private:
	std::map<std::string, int> enchantMap;

public:
	EnchantCommand() : IMCCommand("enchant", "Enchants items", "<enchantment> [level] ") {
		enchantMap["protection"] = 0;
		enchantMap["fire_protection"] = 1;
		enchantMap["feather_falling"] = 2;
		enchantMap["blast_protection"] = 3;
		enchantMap["projectile_protection"] = 4;
		enchantMap["thorns"] = 5;
		enchantMap["respiration"] = 6;
		enchantMap["depth_strider"] = 7;
		enchantMap["aqua_affinity"] = 8;
		enchantMap["frost_walker"] = 25;
		enchantMap["sharpness"] = 9;
		enchantMap["smite"] = 10;
		enchantMap["bane_of_arthropods"] = 11;
		enchantMap["knockback"] = 12;
		enchantMap["fire_aspect"] = 13;
		enchantMap["looting"] = 14;
		enchantMap["channeling"] = 32;
		enchantMap["impaling"] = 29;
		enchantMap["loyalty"] = 31;
		enchantMap["riptide"] = 30;
		enchantMap["silktouch"] = 16;
		enchantMap["fortune"] = 18;
		enchantMap["unbreaking"] = 17;
		enchantMap["efficiency"] = 15;
		enchantMap["mending"] = 26;
		enchantMap["power"] = 19;
		enchantMap["punch"] = 20;
		enchantMap["flame"] = 21;
		enchantMap["infinity"] = 22;
		enchantMap["multishot"] = 33;
		enchantMap["quick_charge"] = 35;
		enchantMap["piercing"] = 34;
		enchantMap["luck_of_sea"] = 23;
		enchantMap["lure"] = 24;
		enchantMap["soul_speed"] = 36;
	}
	~EnchantCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
		int selectedSlot = supplies->selectedHotbarSlot;
		C_ItemStack* item = inv->getItemStack(selectedSlot);
		C_InventoryAction* firstAction = nullptr;
		C_InventoryAction* secondAction = nullptr;
		ItemDescriptor* desc = nullptr;
		desc = new ItemDescriptor((*item->item)->itemId, 0);
		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		assertTrue(args->size() > 1);
		int enchantId = 0;
		int enchantLevel = 32767;

		if (selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == NULL) {
			clientMessageF("%sEnchant failed, no item in hand!", RED);  // Checks for an item in hand. If there is no itrem, it dosernt do anything
			return false;
		}
		//Enchant all
		if (args->at(1) != "all") {
			try {
				// convert text typed to back to lower case
				std::string data = args->at(1);
				std::transform(data.begin(), data.end(), data.begin(), ::tolower);
				auto convertedString = enchantMap.find(data);
				if (convertedString != enchantMap.end())
					enchantId = convertedString->second;
				else
					enchantId = assertInt(args->at(1));
			} catch (int) {
				clientMessageF("exception while trying to get enchant string");
				enchantId = assertInt(args->at(1));
			}
		}

		if (args->size() > 2)
			enchantLevel = assertInt(args->at(2));

		using getEnchantsFromUserData_t = void(__fastcall*)(C_ItemStack*, void*);
		using addEnchant_t = bool(__fastcall*)(void*, __int64);
		using saveEnchantsToUserData_t = void(__fastcall*)(C_ItemStack*, void*);

		static getEnchantsFromUserData_t getEnchantsFromUserData = reinterpret_cast<getEnchantsFromUserData_t>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B F2 48 8B D9 48 89 54 24 ? 33 FF 89 7C 24 ? E8 ? ? ? ? 84 C0"));
		static addEnchant_t addEnchant = reinterpret_cast<addEnchant_t>(FindSignature("48 89 5C 24 ?? 48 89 54 24 ?? 57 48 83 EC ?? 45 0F"));
		static saveEnchantsToUserData_t saveEnchantsToUserData = 0x0;

		//checks if there is an existing enchant
		if (!saveEnchantsToUserData) {
			saveEnchantsToUserData = reinterpret_cast<saveEnchantsToUserData_t>(FindSignature("48 89 5C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B FA 4C 8B C1 48 8B 41 08 48 85 C0"));
		}

		if (strcmp(args->at(1).c_str(), "all") == 0) {
			for (int i = 0; i < 38; i++) {
				void* EnchantData = malloc(0x60);
				if (EnchantData != nullptr)
					memset(EnchantData, 0x0, 0x60);
				getEnchantsFromUserData(item, EnchantData);
				__int64 enchantPair = ((__int64)enchantLevel << 32) | i;
				if (addEnchant(EnchantData, enchantPair))  // Upper 4 bytes = level, lower 4 bytes = enchant type
					saveEnchantsToUserData(item, EnchantData);
				free(EnchantData);
			}
			clientMessageF("%sEnchant successful!", LIGHT_PURPLE);
		} else {
			void* EnchantData = malloc(0x60);
			if (EnchantData != nullptr)
				memset(EnchantData, 0x0, 0x60);
			getEnchantsFromUserData(item, EnchantData);
			__int64 enchantPair = ((__int64)enchantLevel << 32) | enchantId;
			if (addEnchant(EnchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
				saveEnchantsToUserData(item, EnchantData);
				clientMessageF("%sEnchant successful!", GREEN);
			} else
				clientMessageF("%sEnchant failed, try using a lower enchant-level", RED);
			free(EnchantData);
		}

		//dupe item
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == NULL))  // Item in hand?
			return false;
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(*new C_InventoryAction(0, item, nullptr, 507, 99999));
		inv->addItemToFirstEmptySlot(item);
		return true;
	}
	virtual void onTick(C_GameMode* gm) {
		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == NULL))  // Item in hand?
			return;
	}
};