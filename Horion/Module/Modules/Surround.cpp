#include "surround.h"

#include "../../DrawUtils.h"

Surround::Surround() : IModule(0, Category::WORLD, "Surrounds you in obsidian for less damage") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("AntiCity", 1))
				.addEntry(EnumEntry("Normal", 2));
	registerEnumSetting("Mode", &enum1, 2);
	registerBoolSetting("Render", &renderSurround, true);
	registerBoolSetting("Disable Complete", &disableOnComplete2, true);
}

Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}

bool SurroundCheck(vec3_t blockBelow) {
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
			g_Data.getCGameMode()->buildBlock(&blok, i);

			return true;
		}
	}
	return false;
}

void Surround::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())) {
		setEnabled(false);
		return;
	}

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

	vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);

	for (auto surroundBlock : surrArr) {
		auto playerPosition = g_Data.getLocalPlayer()->getPos();
		auto flooredPos = playerPosition->floor();
		flooredPos.y -= 1.f;
		auto mathsBlockPos = flooredPos.add(surroundBlock);

		SurroundCheck(mathsBlockPos);
			surrArr.erase(surrArr.begin());
		break;
	}
	if (surrArr.empty() && disableOnComplete2) setEnabled(false);
}

void Surround::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (renderSurround) {
		if (enum1.selected == 1) {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

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
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

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
				DrawUtils::setColor(1.f, 1.f, 0.f, 1.f);

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