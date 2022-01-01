#include "HiveNuker.h"

HiveNuker::HiveNuker() : IModule(VK_NUMPAD9, Category::SERVER, "Destroys blocks around you") {
	registerIntSetting("Range", &range, range, 1, 8);
}

HiveNuker::~HiveNuker() {
}

const char* HiveNuker::getModuleName() {
	return ("HiveNuker");
}

void HiveNuker::onWorldTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				blockPos = vec3_ti(x, y, z);
				destroy = false;
				gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (gm->player->region->getBlock(blockPos)->toLegacy()->blockId) destroy = true;

				if (destroy) {
					bool isDestroyed = false;
					if (GameData::isLeftClickDown() && g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->canOpenContainerScreen()) {
						PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
						gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
						gm->destroyBlock(new vec3_ti(pointing->block), pointing->blockSide);
						gm->stopDestroyBlock(pointing->block);
					}
					gm->startDestroyBlock(blockPos, gm->player->region->getBlock(blockPos)->data, isDestroyed);
					gm->destroyBlock(&blockPos, gm->player->region->getBlock(blockPos)->data);
					gm->stopDestroyBlock(blockPos);
					g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}
}

void HiveNuker::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>() && g_Data.getLocalPlayer() != nullptr) {
		static auto instaBreakModule = moduleMgr->getModule<InstaBreak>();
		if (destroy) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			auto* authPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(reinterpret_cast<vec3_t&>(blockPos));
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
			authPacket->pitch = angle.x;
			authPacket->yaw = angle.y;
		}
	}
}