#include "Surround.h"

#include "../../DrawUtils.h"
int prevSlot;
vec3_t* center_block;
int y_level = 0;

int tick_runs = 0;

int offset_step = 0;

int old_slot = -1;
Surround::Surround() : IModule(0, Category::WORLD, "Surrounds you with Obsidian") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("Anti-City", 1))
				.addEntry(EnumEntry("Regular", 2))
				.addEntry(EnumEntry("Java", 3));
	enum3 = SettingEnum(this)
				.addEntry(EnumEntry("None", 1))
				.addEntry(EnumEntry("Regular", 2))
				.addEntry(EnumEntry("Java", 3));
	enum2 = SettingEnum(this)
				.addEntry(EnumEntry("Normal", 1))
				.addEntry(EnumEntry("Aurora", 2))
				.addEntry(EnumEntry("Silent", 3));
	registerEnumSetting("Mode", &enum1, 2);
	registerEnumSetting("Rotations", &enum3, 1);
	registerBoolSetting("Swap", &spoofC, true);
	registerEnumSetting("Swap", &enum2, 2);
	registerBoolSetting("Render", &renderSurround, true);
	registerBoolSetting("JumpDisable", &jumpDisable, false);
	registerBoolSetting("AutoCenter", &center, true);
	registerBoolSetting("AntiFacePlace", &block_head, false);
	registerBoolSetting("DisableComplete", &disableOnComplete2, true);
	registerBoolSetting("AntiAnvil", &antianvil, true);
	registerBoolSetting("Packet", &triggerable, true);
	registerBoolSetting("SelfWeb", &selfweb, true);
	registerIntSetting("SwapDelay", &delay2, delay2, 1, 10);
	registerFloatSetting("Blocks Per Tick", &tick_for_place, tick_for_place, 1, 12);
	registerFloatSetting("Ticks til timeout", &tick_timeout, tick_timeout, 10, 50);
}

Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}

int slot = false;

bool Surround::isFlashMode() {
	return false;
}
bool Surround::tryAirPlace(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
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
			if (spoofC) Spoof();
			g_Data.getCGameMode()->buildBlock(&blok, i);
			if (enum2.selected == 3) SilentSwap("item.obsidian");
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		}
	}
	return false;
}
bool Surround::tryScaffold(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return false;

	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}
		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}

		return true;
	}
	return false;
}
int switchCooldown69 = 0;
int previousSlot69 = -1;

bool Surround::Spoof() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();

	int prevSlot = supplies->selectedHotbarSlot;

	auto funny = supplies->inventory->getItemStack(prevSlot);
	if (funny->item != nullptr) {
		if (strcmp(funny->getItem()->tileName.getText(), "item.obsidian") == 0)  // Try blocking that nukkit
			supplies->selectedHotbarSlot = prevSlot;

		for (auto i = 0; i < 9; i++) {
			C_ItemStack* item = supplies->inventory->getItemStack(i);

			if (item->item != nullptr) {
				if (strcmp(item->getItem()->tileName.getText(), "item.obsidian") == 0) {
					supplies->selectedHotbarSlot = i;
					switchCooldown69 = 2;
					previousSlot69 = prevSlot;
					return true;
				}
			}
		}

		return false;
	}
}

vec3_t get_center(double posX, double posY, double posZ) {
	vec3_t xyz = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	xyz.x += 0.5f;
	xyz.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(xyz);
	return vec3_t(xyz.x, xyz.y, xyz.z);
}

bool Surround::AAnvilSwap() {
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
		if (stack->item != nullptr) {
			if (strcmp(stack->getItem()->tileName.getText(), "item.anvil") == 0) {
				g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
				return true;
			}
		}
	}
}

bool Surround::tryAntiAnvil(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
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
			if (AntiAnvilSwap) AAnvilSwap();
			g_Data.getCGameMode()->buildBlock(&blok, i);
			if (enum2.selected == 3) SilentSwap("item.anvil");
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		}
	}
	return false;
}

void Surround::onEnable() {
	old_slot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
	if (Spoof() == -1) {
		setEnabled(false);
		g_Data.getGuiData()->displayClientMessageF("[%sSurround%s] %sNo Obby%s!", GREEN, WHITE, GREEN, GRAY, GRAY);
		return;
	}

	if (g_Data.getLocalPlayer() != nullptr) {
		y_level = (int)round(g_Data.getLocalPlayer()->getPos()->y);

		center_block = &get_center(g_Data.getLocalPlayer()->getPos()->x, g_Data.getLocalPlayer()->getPos()->y, g_Data.getLocalPlayer()->getPos()->z);
		vec3_t moveVec;

		if (center) {
			moveVec.x = 0;
			moveVec.z = 0;
		}
	}

	if (g_Data.getLocalPlayer() != nullptr) {
		y_level = (int)round(g_Data.getLocalPlayer()->getPos()->y);

		center_block = &get_center(g_Data.getLocalPlayer()->getPos()->x, g_Data.getLocalPlayer()->getPos()->y, g_Data.getLocalPlayer()->getPos()->z);
		vec3_t moveVec;

		if (center) {
			moveVec.x = 0;
			moveVec.z = 0;
		}
	}
}

bool Surround::SilentSwap(const char* tile) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (strcmp(stack->getItem()->tileName.getText(), tile) == 0) {
					C_MobEquipmentPacket a(id, *stack, n, n);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					return true;
				}
			}
		}
	}
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;
}


void Surround::onDisable() {
	g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
}
bool doReset = true;
bool iFuckedUp2 = false;
int tDelay2 = 0;
std::vector<vec3_t> surrArr;
void Surround::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	switch (enum2.selected) {
	case 0:
		blockSwap = false;
		AntiAnvilSwap = false;
		silentBlockSwap = false;
		break;
	case 1:
		blockSwap = true;
		AntiAnvilSwap = true;
		silentBlockSwap = false;
		break;
	}
	if (enum2.selected == 3) {
	// Silent Switch For Aurora
		blockSwap = false;
		AntiAnvilSwap = false;
		silentBlockSwap = true;
	}
	switch (enum3.selected) {
	case 0:
		rot1 = false;
		rotate = false;
		break;
	case 1:
		rot1 = true;
		rotate = false;
		break;
	case 2:
		rot1 = false;
		rotate = true;
		break;
	}
	switch (enum1.selected) {
	case 0:
		vanilla = false;
		java = false;
		anticity = true;
		break;
	case 1:
		vanilla = true;
		java = false;
		anticity = false;
		break;
	case 2:
		vanilla = false;
		java = true;
		anticity = false;
		break;
	}
	{}

	vec3_t moveVec;
	if (gm->player != nullptr) {
		if (center_block != 0 && center) {
			double x_diff = abs(center_block->x - g_Data.getLocalPlayer()->getPos()->x);
			double z_diff = abs(center_block->z - g_Data.getLocalPlayer()->getPos()->z);
		}

		if ((int)round(g_Data.getLocalPlayer()->getPos()->y) != y_level) {
			setEnabled(false);
			return;
		}

		if (!triggerable && tick_runs >= tick_timeout) {  // timeout time
			tick_runs = 0;
			setEnabled(false);
			return;
		}

		int blocks_placed = 0;

		while (blocks_placed < tick_for_place) {
			if (offset_step >= (block_head ? surround_targets_face.size() : surround_targets.size())) {
				offset_step = 0;
				break;
			}

			auto playerPosition = g_Data.getLocalPlayer()->getPos();
			auto flooredPos = playerPosition->floor();
			flooredPos.y -= 1.f;
			vec3_t* offsetPos = new vec3_t(block_head ? surround_targets_face[offset_step] : surround_targets[offset_step]);
			vec3_t* targetPos = new vec3_t(flooredPos.add(offsetPos->x, offsetPos->y, offsetPos->z));
			bool destroy = false;

			bool try_to_place = true;

			if (!g_Data.getLocalPlayer()->region->getBlock(*targetPos)->blockLegacy->material->isReplaceable) {
				try_to_place = false;
			}
			if (rotate) {
				auto player = g_Data.getLocalPlayer();
				player->pitch = offsetPos->z;
				player->bodyYaw = offsetPos->x;
			}
			vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
			blockBelow.y -= g_Data.getLocalPlayer()->height;
			blockBelow.y -= 0.5f;
			if (rot1) {
				for (int i = 0; i < 40; i++) {
					auto player = g_Data.getLocalPlayer();
					player->pitch = blockBelow.y;
					player->bodyYaw = blockBelow.y;
				}
			}
			offset_step++;
			g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = old_slot;
		}

		tick_runs++;
	}
	g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = old_slot;

	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (surrArr.empty()) {
		doReset = true;
	} else {
		doReset = false;
	}
	if (doReset == true) {
		surrArr.clear();

		if (enum1.selected == 1)
			for (auto surroundBlock : regularBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
		if (enum1.selected == 0)
			for (auto surroundBlock : antiCityBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
	}
	// cant be arsed looking at this rn

	//	if (enum1.selected == 1) {
	for (auto surroundBlock : surrArr) {
		auto playerPosition = g_Data.getLocalPlayer()->getPos();
		auto flooredPos = playerPosition->floor();
		flooredPos.y -= 1.f;
		auto mathsBlockPos = flooredPos.add(surroundBlock);

		if (!tryAntiAnvil(mathsBlockPos))
			;
		surrArr.erase(surrArr.begin());
		break;
	}
	//}
	if (blockSwap) {
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
		iFuckedUp2 = false;
	}

	if (surrArr.empty() && disableOnComplete2) setEnabled(false);

	if (KindaSpoof) {
		if (surrArr.empty()) g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
	}

	if (blockSwap) {
		Odelay2++;
		if (Odelay2 > delay2 * 30) {
			int slot = 1;
			for (int n = 0; n < 9; n++) {
				C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
				if (stack->item != nullptr) {
					if (stack->getItem()->itemId == 49) {
						slot = n;
						g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
						delay2 = 0;
					}
					if (selfweb) {
						for (int n = 0; n < 9; n++) {
							C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
							if (stack->item != nullptr) {
								if (stack->getItem()->itemId == 30) {
									g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
								}
							}
							int place = 1;

							vec3_t blockSide = g_Data.getLocalPlayer()->eyePos0;

							blockSide.y -= g_Data.getLocalPlayer()->height - 1;

							if (!tryScaffold(blockSide)) {
								blockSide.y -= 0;
								blockSide.x -= 0;
							}
						}
					}
				}
			}
		}
	}

	if (antianvil) {
		vec3_t blockSide1 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide2 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide3 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide4 = g_Data.getLocalPlayer()->eyePos0;

		blockSide.y -= g_Data.getLocalPlayer()->height - 1;

		if (!tryAntiAnvil(blockSide)) {
			blockSide.y -= 0;
		}
	}

	if (enum1.selected == 2) {
		vec3_t blockSide1 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide2 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide3 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide4 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide12 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide23 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide34 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSide45 = g_Data.getLocalPlayer()->eyePos0;

		vec3_t blockSideL1M = g_Data.getLocalPlayer()->eyePos0;

		blockSide1.x -= g_Data.getLocalPlayer()->height - 1;
		blockSide1.y -= g_Data.getLocalPlayer()->height - 1;

		blockSide2.x += g_Data.getLocalPlayer()->height - 1;
		blockSide2.y -= g_Data.getLocalPlayer()->height - 1;

		blockSide3.z -= g_Data.getLocalPlayer()->height - 1;
		blockSide3.y -= g_Data.getLocalPlayer()->height - 1;

		blockSide4.z += g_Data.getLocalPlayer()->height - 1;
		blockSide4.y -= g_Data.getLocalPlayer()->height - 1;

		blockSide12.x -= g_Data.getLocalPlayer()->height - 1;
		blockSide12.y -= g_Data.getLocalPlayer()->height - 0;

		blockSide23.x += g_Data.getLocalPlayer()->height - 1;
		blockSide23.y -= g_Data.getLocalPlayer()->height - 0;

		blockSide34.z -= g_Data.getLocalPlayer()->height - 1;
		blockSide34.y -= g_Data.getLocalPlayer()->height - 0;

		blockSide45.z += g_Data.getLocalPlayer()->height - 1;
		blockSide45.y -= g_Data.getLocalPlayer()->height - 0;

		blockSideL1M.y -= g_Data.getLocalPlayer()->height - 1;

		blockSideL1M.y -= g_Data.getLocalPlayer()->height - 1;

		blockSideL1M.y -= g_Data.getLocalPlayer()->height - 1;

		blockSideL1M.y -= g_Data.getLocalPlayer()->height - 1;

		blockSideL1M.y -= g_Data.getLocalPlayer()->height - 1;

		if (!tryAirPlace(blockSide1)) {
			blockSide1.y -= 0;
			blockSide1.x -= 0;
		}

		if (!tryAirPlace(blockSide2)) {
			blockSide2.y += 0;
			blockSide2.x += 0;
		}

		if (!tryAirPlace(blockSide3)) {
			blockSide3.y -= 0;
			blockSide3.z -= 0;
		}

		if (!tryAirPlace(blockSide4)) {
			blockSide4.y += 0;
			blockSide4.z += 0;
		}

		if (!tryAirPlace(blockSide12)) {
			blockSide12.y -= 0;
			blockSide12.x -= 0;
		}

		if (!tryAirPlace(blockSide23)) {
			blockSide23.y += 0;
			blockSide23.x += 0;
		}

		if (!tryAirPlace(blockSide34)) {
			blockSide34.y -= 0;
			blockSide34.z -= 0;
		}

		if (!tryAirPlace(blockSide45)) {
			blockSide45.y += 0;
			blockSide45.z += 0;
		}
		if (!tryAirPlace(blockSideL1M)) {
			blockSideL1M.y -= 0;
		}
	}
}

void Surround::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (jumpDisable && hand->isJumping) setEnabled(false);
}

void Surround::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (renderSurround) {
		if (enum1.selected == 1) {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else if (enum1.selected == 0) {
			for (auto surroundBlock : antiCityBlocks) {
				DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}
		}
	}
}