#include "HiveFly.h"
int counter = 0;
HiveFly::HiveFly() : IModule('0', Category::SERVER, "Turn it on, Throw a pearl, then start flying!!") {
	registerFloatSetting("Speed", &speed, speed, 0.01f, 0.50f);
	registerFloatSetting("Timer", &timer, timer, 20.f, 100.f);
}

HiveFly::~HiveFly() {
}

const char* HiveFly::getModuleName() {
	return ("HivePearlFly");
}

void HiveFly::onEnable() {
	srand(time(NULL));
	counter = 0;
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	slot = supplies->selectedHotbarSlot;
	supplies->selectedHotbarSlot = slot;
	findBlock();
}

void HiveFly::onTick(C_GameMode* gm) {
	float rotChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.f)) + 1.f;
	counter++;
	if (counter <= 10) {
		findBlock();
		auto player = g_Data.getLocalPlayer();
		C_MovePlayerPacket mpp(player, *player->getPos());
		mpp.onGround = player->onGround;
		mpp.pitch = 90.f - rotChange;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
		Utils::rightClick();
	}
	gm->player->velocity.y = 0.f;
	if (isEnabled())
		*g_Data.getClientInstance()->minecraft->timer = timer;
}

bool HiveFly::findBlock() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 36; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->itemId == 422) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			}
		}
	}
	return false;
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	if (counter >= 15) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = 0.f;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
		if (!pressed) {
			player->velocity.x = 0;
			player->velocity.z = 0;
		}
		if (g_Data.canUseMoveKeys()) {
			if (input->isJumping) {
				player->velocity.y += speed;
			}
			if (input->isSneakDown) {
				player->velocity.y -= speed;
			}
		}

		if (player == nullptr)
			return;

		std::vector<vec3_ti> sideBlocks;
		sideBlocks.reserve(8);
		if (!pressed)
			return;
		moveVec2d = moveVec2d.normalized();
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		for (int x = -1; x <= 1; x++) {
			for (int z = -1; z <= 1; z++) {
				if (x == 0 && z == 0)
					continue;
				if (moveVec2d.dot(vec2_t(x, z).normalized()) < 0.6f)
					continue;
				sideBlocks.push_back(vec3_ti(x, 0, z));
			}
		}
		auto pPos = *player->getPos();
		pPos.y = player->aabb.lower.y;
		auto pPosI = vec3_ti(pPos.floor());
		auto isObstructed = [&](int yOff, AABB* obstructingBlock = nullptr, bool ignoreYcoll = false) {
			for (const auto& current : sideBlocks) {
				vec3_ti side = pPosI.add(0, yOff, 0).add(current);
				if (side.y < 0 || side.y >= 256)
					break;
				auto block = player->region->getBlock(side);
				if (block == nullptr || block->blockLegacy == nullptr)
					continue;
				C_BlockLegacy* blockLegacy = block->toLegacy();
				if (blockLegacy == nullptr)
					continue;
				AABB collisionVec;
				if (!blockLegacy->getCollisionShape(&collisionVec, block, player->region, &side, player))
					continue;
				bool intersects = ignoreYcoll ? collisionVec.intersectsXZ(player->aabb.expandedXZ(0.1f)) : collisionVec.intersects(player->aabb.expandedXZ(0.1f));

				if (intersects) {
					if (obstructingBlock != nullptr)
						*obstructingBlock = collisionVec;
					return true;
				}
			}
			return false;
		};

		AABB lowerObsVec, upperObsVec;
		bool upperObstructed = isObstructed(1, &upperObsVec);

		bool lowerObstructed = isObstructed(0, &lowerObsVec);
		float targetSpeed = speed;
		//actually moving code
		if (upperObstructed || lowerObstructed) {
			setEnabled(false);
		}
	} else {
		g_Data.getLocalPlayer()->velocity.x = 0;
		g_Data.getLocalPlayer()->velocity.y = 0;
		g_Data.getLocalPlayer()->velocity.z = 0;
	}
}

void HiveFly::onSendPacket(C_Packet* packet) {
}

void HiveFly::onLevelRender() {
}

void HiveFly::onDisable() {
	counter = 0;
	if (g_Data.getLocalPlayer() != nullptr) {
		auto player = g_Data.getLocalPlayer();
		player->velocity.y = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}