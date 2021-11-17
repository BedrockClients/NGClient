#include "BlockEsp.h"

BlockEsp::BlockEsp() : IModule(0x0, Category::VISUAL, "Draws a box around specific blocks") {
	registerIntSetting("radius", &range, range, 5, 35);
	registerBoolSetting("Outline shape", &outline, outline);
	registerFloatSetting("Outline Thickness", &thick, thick, 0.1f, 0.8f);
	registerBoolSetting("Emerald ore", &emerald, emerald);
	registerBoolSetting("Diamond ore", &diamond, diamond);
	registerBoolSetting("All Gold ores", &gold, gold);
	registerBoolSetting("Redstone ore", &redstone, redstone);
	registerBoolSetting("Lapis ore", &lapis, lapis);
	registerBoolSetting("Iron ore", &iron, iron);
	registerBoolSetting("Coal ore", &coal, coal);
	registerBoolSetting("Copper ore", &copper, copper);
	registerBoolSetting("Ancient Debris", &debris, debris);
	registerBoolSetting("Nether Quartz", &quartz, quartz);
	registerBoolSetting("Invisible Blocks", &invisBlocks, invisBlocks);
	registerBoolSetting("Portal Blocks", &portalBlocks, portalBlocks);
}

BlockEsp::~BlockEsp() {
}

const char* BlockEsp::getModuleName() {
	return ("BlockESP");
}

void BlockEsp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			Odelay++;
			if (Odelay > delay * 20) {
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
								if (diamond) {
									if (blockId == 56) render0 = true;
								}
								if (emerald) {
									if (blockId == 129) render1 = true;
								}
								if (gold) {
									if (blockId == 14 || blockId == 536 || blockId == 543) render2 = true;
								}
								if (redstone) {
									if (blockId == 73 || blockId == 74) render3 = true;
								}
								if (lapis) {
									if (blockId == 21) render4 = true;
								}
								if (iron) {
									if (blockId == 15) render5 = true;
								}
								if (coal) {
									if (blockId == 16) render6 = true;
								}
								if (debris) {
									if (blockId == 526) render7 = true;
								}
								if (quartz) {
									if (blockId == 153) render8 = true;
								}
								if (invisBlocks) {
									if (blockId == 95 || blockId == 416) render9 = true;
								}
								if (portalBlocks) {
									if (blockId == 90 || blockId == 119) render10 = true;
								}
								if (copper) {
									if (blockId == 566 || blockId == 236) render11 = true;
								}

								//deepslate
								if (diamond) {
									if (blockId == 660) render0 = true;
								}
								if (emerald) {
									if (blockId == 662) render1 = true;
								}
								if (gold) {
									if (blockId == 657 || blockId == 536 || blockId == 543) render2 = true;
								}
								if (redstone) {
									if (blockId == 658 || blockId == 292) render3 = true;
								}
								if (redstone) {
									if (blockId == 659 || blockId == 293) render3 = true;
								}
								if (lapis) {
									if (blockId == 655) render4 = true;
								}
								if (iron) {
									if (blockId == 656) render5 = true;
								}
								if (coal) {
									if (blockId == 661) render6 = true;
								}
								if (copper) {
									if (blockId == 663 || blockId == 297) render11 = true;
								}

								//Block
								if (debris) {
									if (blockId == 525) render7 = true;
								}

								if (redstone) {
									if (blockId == 152) render3 = true;
								}

								if (coal) {
									if (blockId == 173) render6 = true;

									if (gold) {
										if (blockId == 41) render2 = true;
									}

									if (iron) {
										if (blockId == 42) render5 = true;
									}

									if (emerald) {
										if (blockId == 133) render1 = true;
									}

									if (diamond) {
										if (blockId == 57) render0 = true;
									}

									if (lapis) {
										if (blockId == 22) render4 = true;
									}

									if (copper) {
										if (blockId == 595) render11 = true;
									}

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

										//copper
										if (render11) {
											DrawUtils::setColor(0.9f, 1.f, 0.1f, 1);
											DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
										}
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
}