#include "BlockEsp.h"
#include "../../DrawUtils.h"

BlockEsp::BlockEsp() : IModule(VK_NUMPAD9, Category::WORLD, "ESP, but for storage") {
	registerIntSetting("Range", &range, range, 1, 100);
	registerBoolSetting("Redstone", &redstone, redstone);
	registerBoolSetting("Diamond", &diamond, diamond);
	registerBoolSetting("Emerald", &emerald, emerald);
}

BlockEsp::~BlockEsp() {
}

const char* BlockEsp::getModuleName() {
	return ("BlockESP");
}

void BlockEsp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys() || !g_Data.isInGame())) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3_t blockPos = vec3_t(x, y, z);
						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						int id = block->toLegacy()->blockId;
						bool draw = false;
						if (id == 73 && redstone) draw = true;     // Lit Redstone
						if (id == 74 && redstone) draw = true;     // Redstone
						if (id == 56 && diamond) draw = true;      // Diamond
						if (id == 129 && emerald) draw = true;     // Emerald
						if (draw) {
						static auto Surge = moduleMgr->getModule<ClickGuiMod>();
						if (Surge->surge)
						DrawUtils::setColor(0.f, 0.f, 1.f, 1);
						else
						DrawUtils::setColor(0.5f, 0.f, 1.f, 1);

						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), 0.2f);
					}
				}
			}
		}
	}
}