#pragma once

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "CBlockLegacy.h"
#include "CClientInstance.h"
class Tessellator {
private:
	char pad_0000[0x128];
	vec3_t transformOffset; // 0x128

public:
	void addPostTransformOffset(int x, int y, int z) {
		addPostTransformOffset((float)x, (float)y, (float)z);
	}
	void addPostTransformOffset(float x, float y, float z) { this->transformOffset = this->transformOffset.add(x, y, z); }
};

class C_Block;

namespace mce {
class Mesh;
}

class BlockTessellator {
public:
	mce::Mesh* getMeshForBlockInWorld(Tessellator* t, C_Block* block, vec3_ti& pos) {
		using BT_getMeshForBlockInWorld_t = mce::Mesh* (*)(BlockTessellator*, Tessellator*, C_Block*, vec3_ti&, int, __int64);
		static BT_getMeshForBlockInWorld_t getMeshForBlock = reinterpret_cast<BT_getMeshForBlockInWorld_t>(FindSignature("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? FE FF FF FF 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4D 8B F1 4D 8B F8 48"));

		return getMeshForBlock(this, t, block, pos, block->getRenderLayer(), 0);
	}
};