#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class BlockEsp : public IModule {
public:
	float thick = 0.4f;
	bool copper = false;
	bool outline = false;
	bool diamond = false;
	bool emerald = false;
	bool gold = false;
	bool redstone = false;
	bool lapis = false;
	bool iron = false;
	bool coal = false;
	bool debris = false;
	bool quartz = false;
	bool invisBlocks = false;
	bool portalBlocks = false;
	int range = 10;
	int Odelay = 0;
	float delay = 0.14f;

	BlockEsp() : IModule(0x0, Category::VISUAL, "Draws a box around specific blocks") {
		registerIntSetting("radius", &range, range, 3, 20);
		registerBoolSetting("Outline shape", &outline, outline);
		registerFloatSetting("Outline Thickness", &thick, thick, 0.1f, 0.8f);
		registerBoolSetting("Emerald ore", &emerald, emerald);
		registerBoolSetting("Diamond ore", &diamond, diamond);
		registerBoolSetting("Gold ore", &gold, gold);
		registerBoolSetting("Redstone ore", &redstone, redstone);
		registerBoolSetting("Lapis ore", &lapis, lapis);
		registerBoolSetting("Iron ore", &iron, iron);
		registerBoolSetting("Coal ore", &coal, coal);
		registerBoolSetting("Copper ore", &copper, copper);
		registerBoolSetting("Ancient Debris", &debris, debris);
		registerBoolSetting("Nether Quartz", &quartz, quartz);
		registerBoolSetting("Invisible Blocks", &invisBlocks, invisBlocks);
		registerBoolSetting("Portal Blocks", &portalBlocks, portalBlocks);
	};
	~BlockEsp(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			if (g_Data.isInGame()) {
				Odelay++;
				if (Odelay > delay * 20) {  // to stop lag
					vec3_t* pos = g_Data.getLocalPlayer()->getPos();
					for (int x = (int)pos->x - range; x < pos->x + range; x++) {
						for (int z = (int)pos->z - range; z < pos->z + range; z++) {
							for (int y = (int)pos->y - range; y < pos->y + range; y++) {
								vec3_t blockPos = vec3_t(x, y, z);

								C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
								if (block != nullptr) {
									int blockId = block->toLegacy()->blockId;
									bool render0 = false;
									bool render1 = false;
									bool render2 = false;
									bool render3 = false;
									bool render4 = false;
									bool render5 = false;
									bool render6 = false;
									bool render7 = false;
									bool render8 = false;
									bool render9 = false;
									bool render10 = false;
									bool render11 = false;

									//ore
									if (diamond)
										if (blockId == 56 || blockId == 660 || blockId == 57) render0 = true;
									if (emerald)
										if (blockId == 129 || blockId == 662 || blockId == 133) render1 = true;
									if (gold)
										if (blockId == 14 || blockId == 536 || blockId == 543 || blockId == 657 || blockId == 536 || blockId == 543 || blockId == 41) render2 = true;
									if (redstone)
										if (blockId == 73 || blockId == 74 || blockId == 658 || blockId == 292 || blockId == 659 || blockId == 293 || blockId == 152) render3 = true;
									if (lapis)
										if (blockId == 21 || blockId == 655 || blockId == 22) render4 = true;
									if (iron)
										if (blockId == 15 || blockId == 656 || blockId == 42) render5 = true;
									if (coal)
										if (blockId == 16 || blockId == 661 || blockId == 173) render6 = true;
									if (debris)
										if (blockId == 526 || blockId == 525) render7 = true;
									if (quartz)
										if (blockId == 153) render8 = true;
									if (invisBlocks)
										if (blockId == 95 || blockId == 416) render9 = true;
									if (portalBlocks)
										if (blockId == 90 || blockId == 119) render10 = true;
									if (copper)
										if (blockId == 566 || blockId == 236 || blockId == 663 || blockId == 297 || blockId == 595) render11 = true;

									//diamond
									if (render0) {
										DrawUtils::setColor(0.f, 1.f, 1.f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//emerald
									if (render1) {
										DrawUtils::setColor(0.1f, 0.9f, 0.f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//gold
									if (render2) {
										DrawUtils::setColor(0.9f, 1.f, 0.1f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//redstone
									if (render3) {
										DrawUtils::setColor(1.f, 0.1f, 0, 1.f);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//lapis
									if (render4) {
										DrawUtils::setColor(0.1f, 0.2f, 0.7f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//iron
									if (render5) {
										DrawUtils::setColor(0.7f, 0.5f, 0.4f, 1.f);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//coal
									if (render6) {
										DrawUtils::setColor(0.f, 0.f, 0.f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//debris
									if (render7) {
										DrawUtils::setColor(0.5f, 0.2f, 0.f, 1.f);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//quartz
									if (render8) {
										DrawUtils::setColor(1.f, 1.f, 1.f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//invisBlocks
									if (render9) {
										DrawUtils::setColor(0.3f, 0.1f, 0.6f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//portals
									if (render10) {
										DrawUtils::setColor(0.9f, 0.4f, 1.f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
									//copper
									if (render11) {
										DrawUtils::setColor(0.9f, 1.f, 0.1f, 1);
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
									}
								}
							}
							Odelay = 0;
						}
					}
				}
			}
		}
	}

	virtual const char* getModuleName() override {
		return "BlockEsp";
	}
};