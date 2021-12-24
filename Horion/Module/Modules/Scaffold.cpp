#include "Scaffold.h"

#include "../../../Utils/Logger.h"
#include "../ModuleManager.h"
uintptr_t HiveBypass1 = Utils::getBase() + 0x8F3895;  // Second one of 89 41 18 0F B6 42 ?? 88 41 ?? F2 0F 10 42 ?? F2 0F 11 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ??
uintptr_t HiveBypass2 = Utils::getBase() + 0x8F87C7;  // C7 40 18 03 00 00 00 48 8B 8D

Scaffold::Scaffold() : IModule(VK_NUMPAD1, Category::WORLD, "Automatically build blocks beneath you") {
	registerBoolSetting("Spoof", &spoof, spoof);
	registerBoolSetting("AirPlace", &airplace, airplace);
	registerBoolSetting("Auto Select", &autoselect, autoselect);
	registerBoolSetting("Predict", &predict, predict);
	registerBoolSetting("Hive", &rot, rot);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
	registerBoolSetting("Y Lock", &yLock, yLock);
	registerBoolSetting("Staircase Mode", &staircaseMode, staircaseMode);
}

Scaffold::~Scaffold() {
}

const char* Scaffold::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (airplace) {
			return "Scaffold [Air]";
		} else if (spoof) {
			return "Scaffold [Spoof]";
		} else if (predict) {
			return "Scaffold [Predict]";
		} else if (staircaseMode)
			return "Scaffold [Stairs]";
		else if (autoselect)
			return "Scaffold [AutoSelect]";
		else return "Scaffold";
	} else
		return "Scaffold";
}

void Nop(BYTE* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

bool Scaffold::tryScaffold(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);
		int i = 0;
		if (airplace) {
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		} else {
			static std::vector<vec3_ti*> checklist;
			bool foundCandidate = false;
			if (checklist.empty()) {
				checklist.push_back(new vec3_ti(0, -1, 0));
				checklist.push_back(new vec3_ti(0, 1, 0));

				checklist.push_back(new vec3_ti(0, 0, -1));
				checklist.push_back(new vec3_ti(0, 0, 1));

				checklist.push_back(new vec3_ti(-1, 0, 0));
				checklist.push_back(new vec3_ti(1, 0, 0));
			}

			for (auto current : checklist) {
				vec3_ti calc = blok.sub(*current);
				bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
				if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
					// Found a solid block to click
					foundCandidate = true;
					blok = calc;
					break;
				}
				i++;
			}
			if (foundCandidate) {
				g_Data.getCGameMode()->buildBlock(&blok, i);
				return true;
			}
			//g_Data.getCGameMode()->buildBlock(&blok, i);
		}
	}
	return false;
}

bool Scaffold::findBlock() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 36; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->isBlock()) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			}
		}
	}
	return false;
}

void Scaffold::onTick(C_GameMode* gm) {

	//float Pitch = (gm->player->pitch) * -(PI / 180); Correct Pitch
	if (rot) {
		g_Data.getLocalPlayer()->pointingStruct->rayHitType = 0;
		Nop((BYTE*)HiveBypass1, 3);
		Patch((BYTE*)HiveBypass2, (BYTE*)"\xC7\x40\x18\x00\x00\x00\x00", 7);
	}

	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	if (autoselect) {
		findBlock();
	}
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()) && !spoof)  // Block in hand?
		return;

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1

	if (staircaseMode) {
		vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
		blockBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelow.y -= 1.5f;

		vec3_t blockBelowBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 2 blocks below the player
		blockBelowBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelowBelow.y -= 2.0f;

		if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow)) {
			if (speed > 0.05f) {  // Are we actually walking?
				blockBelow.z -= vel.z * 0.4f;
				blockBelowBelow.z -= vel.z * 0.4f;
				if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow)) {
					blockBelow.x -= vel.x * 0.4f;
					blockBelowBelow.x -= vel.x * 0.4f;
					if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow.z += vel.z;
						blockBelow.x += vel.x;
						blockBelowBelow.z += vel.z;
						blockBelowBelow.x += vel.x;
						tryScaffold(blockBelow);
						tryScaffold(blockBelowBelow);
					}
				}
			}
		}
	} else {
		if (yLock) {
			blockBelowtest2.y = blockBelowtest.y;
		} else {
			blockBelowtest2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
			blockBelowtest2.y -= 2.5f;
		}

			blockBelowtest2.z -= vel.z * 0.4f;
		if (!tryScaffold(blockBelowtest2)) {
				blockBelowtest2.x -= vel.x * 0.4f;
			blockBelowtest2.z += vel.z;
				blockBelowtest2.x += vel.x;
			tryScaffold(blockBelowtest2);
				blockBelowtest2.z -= vel.z * 0.3f;
				if (predict) {
					if (!tryScaffold(blockBelowtest2)) {
						blockBelowtest2.x -= vel.x / 3.5f;
						blockBelowtest2.z += vel.z;
						blockBelowtest2.x += vel.x;
						tryScaffold(blockBelowtest2);
						blockBelowtest2.z -= vel.z / 3.5f;
					}
				}
			}
		if (!tryScaffold(blockBelowtest2)) {
			if (speed > 0.05f) {
				blockBelowtest2.z -= vel.z * 0.3f;
				if (!tryScaffold(blockBelowtest2)) {
					blockBelowtest2.x -= vel.x * 0.3f;
					if (!tryScaffold(blockBelowtest2) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelowtest2.z += vel.z;
						blockBelowtest2.x += vel.x;
						tryScaffold(blockBelowtest2);
					}
				}
			}
		}
		if (!tryScaffold(blockBelowtest2)) {
			if (speed > 0.05f) {
				blockBelowtest2.z -= vel.z * 0.3f;
				if (!tryScaffold(blockBelowtest2)) {
					blockBelowtest2.x -= vel.x * 0.3f;
					if (!tryScaffold(blockBelowtest2) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelowtest2.z += vel.z;
						blockBelowtest2.x += vel.x;
						tryScaffold(blockBelowtest2);
					}
				}
			}
		}
		}
	if (spoof) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = slot;
	}
}

void Scaffold::onLevelRender() {
}

void Scaffold::onSendPacket(C_Packet* packet) {
}

void Scaffold::onEnable() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	slot = supplies->selectedHotbarSlot;
	blockBelowtest.y = g_Data.getLocalPlayer()->eyePos0.y;  // Block below the player
	blockBelowtest.y -= 2.5f;
}
void Scaffold::onDisable() {
	Patch((BYTE*)HiveBypass1, (BYTE*)"\x89\x41\x18", 3);
	Patch((BYTE*)HiveBypass2, (BYTE*)"\xC7\x40\x18\x03\x00\x00\x00", 7);
}