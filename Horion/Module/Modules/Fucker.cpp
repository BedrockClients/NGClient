#include "Fucker.h"

Fucker::Fucker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys specific things around you") {
	registerBoolSetting("Hive Bypass", &bypass, bypass);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
	registerIntSetting("Range", &range, range, 1, 10);
	registerBoolSetting("Beds", &beds, beds);
	registerBoolSetting("Eggs", &eggs, eggs);
	registerBoolSetting("Cakes", &cakes, cakes);
	registerBoolSetting("Treasures", &treasures, treasures);
	registerBoolSetting("Chests", &chests, chests);
	registerBoolSetting("Redstone", &redstone, redstone);
	registerBoolSetting("Diamonds", &diamond, diamond);
	registerBoolSetting("Emeralds", &emerald, emerald);
}

Fucker::~Fucker() {
}

const char* Fucker::getModuleName() {
	return ("Breaker");
}

void Fucker::onTick(C_GameMode* gm) {
	if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->localPlayer->isAlive()) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					blockPos = vec3_ti(x, y, z);
					destroy = false;
					bool eat = false;
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

					if (id == 26 && beds) destroy = true;                                          // Beds
					if (id == 122 && eggs) destroy = true;                                         // Dragon Eggs
					if (id == 92 && cakes) eat = true;                                             // Cakes
					if (id == 54 && chests) destroy = true;                                        // Chests
					if (id == 73 && redstone && gm->player->getAbsorption() < 10) destroy = true;  // Lit Redstone
					if (id == 74 && redstone && gm->player->getAbsorption() < 10) destroy = true;  // Redstone
					if (id == 56 && diamond) destroy = true;                                       // Diamond
					if (id == 129 && emerald) destroy = true;                                      // Emerald

					if (destroy) {
						if (!bypass)
							gm->destroyBlock(&blockPos, 0);
						else {
							bool isDestroyed = false;
							if (GameData::isLeftClickDown() && g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->canOpenContainerScreen()) {
								PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
								gm->stopDestroyBlock(pointing->block);
								gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
								gm->destroyBlock(new vec3_ti(pointing->block), pointing->blockSide);
							}
							gm->stopDestroyBlock(blockPos);
							gm->startDestroyBlock(blockPos, gm->player->region->getBlock(blockPos)->data, isDestroyed);
							gm->destroyBlock(&blockPos, gm->player->region->getBlock(blockPos)->data);
						}
					}
					if (eat) {
						gm->buildBlock(&blockPos, 0);
						if (!noSwing)
							g_Data.getLocalPlayer()->swingArm();
						return;
					}
				}
			}
		}
		if (destroy) {
			srand(time(NULL));
			auto pos2 = *g_Data.getLocalPlayer()->getPos();
			float targetX = (float)(blockPos.x) - (float)(pos2.x);
			float targetY = (float)(blockPos.y) - (float)(pos2.y);
			float targetZ = (float)(blockPos.z) - (float)(pos2.z);
			float breakAimX = atan2f(targetZ, targetX) * (180.f / PI) - 90.f;
			float breakAimY = atan2f(targetY, sqrtf((targetX * targetX) + (targetZ * targetZ))) * (-180.f / PI);
			float xChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.f));
			xChange -= 5.f;
			float yChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5.f));
			yChange -= 2.5f;
			C_MovePlayerPacket pkt;
			pkt.Position = pos2;
			pkt.pitch = breakAimX + yChange;
			pkt.yaw = breakAimY + xChange;
			pkt.onGround = g_Data.getLocalPlayer()->onGround;
			pkt.entityRuntimeID = g_Data.getLocalPlayer()->entityRuntimeId;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
		}
	}
}
void Fucker::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>() && g_Data.getLocalPlayer() != nullptr && bypass) {
		static auto instaBreakModule = moduleMgr->getModule<InstaBreak>();
		if (destroy) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(reinterpret_cast<vec3_t&>(blockPos));
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}

void Fucker::onLevelRender() {
	if (treasures) {
		if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->localPlayer->isAlive()) {
			g_Data.forEachEntity([](C_Entity* ent, bool b) {
				std::string name = ent->getNameTag()->getText();
				int id = ent->getEntityTypeId();
				if (name.find("Treasure") != std::string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
					g_Data.getCGameMode()->attack(ent);
					auto breakMod = moduleMgr->getModule<Fucker>();
					if (!breakMod->noSwing)
					g_Data.getLocalPlayer()->swingArm();
				}
			});
		}
	}
}