#include "BlockFly.h"

BlockFly::BlockFly() : IModule(0, Category::FLYS, "Block Fly") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 0.7f);
	registerIntSetting("Timer Speed", &timer, timer, 20, 200);
	registerBoolSetting("Timer", &time, time);
	registerBoolSetting("Damage", &dmg, dmg);
	registerBoolSetting("Fail Safe", &safe, safe);
}

BlockFly::~BlockFly() {
}

const char* BlockFly::getModuleName() {
	auto HUD = moduleMgr->getModule<HudModule>();
	if (isEnabled() && HUD->bools) {
		if (safe) {
			return "BlockFly [Safe]";
		} else if (dmg) {
			return "BlockFly [Damage]";
		} else if (time) {
			return "BlockFly [Timer]";
		} else
			return "BlockFly";
	} else
		return "BlockFly";
}

void BlockFly::onEnable() {
	if (dmg) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		// player->animateHurt();
	}
}

void BlockFly::onMove(C_MoveInputHandler* input) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (!player->onGround) {
		g_Data.getGuiData()->displayClientMessageF("[%sBlockFly%s] %sU Cant Start In The Air Idiot%s!", BLUE, WHITE, BLUE, WHITE, configMgr, WHITE);
		if (safe) {
			player->velocity.y = 0.00f;
			player->velocity.y = 0.00f;
			player->velocity.y = 0.00f;
			auto scaff = moduleMgr->getModule<Scaffold>();
			scaff->setEnabled(true);
		}
		setEnabled(false);
		return;
	}
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	// if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())) {  // Block in hand?
	// clientMessageF("U Have No Blocks In Ur Inventory :/");
	// setEnabled(false);
	// }
	if (pressed) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = 0.00f;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}

	if (pressed && counter >= 0) {
		auto blinkMod = moduleMgr->getModule<Scaffold>();
		if (blinkMod->isEnabled()) {
			blinkMod->setEnabled(false);
		}
	}
	if (pressed && counter == 6) {
		auto blinkMod = moduleMgr->getModule<Scaffold>();
		if (Fly) {
			blinkMod->setEnabled(true);
		}
	}
	if (pressed && counter == 4) {
		// auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		// if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())  // Block in hand?
		// return;
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
		// C_LocalPlayer* player = g_Data.getLocalPlayer();
		// player->jumpFromGround();
	}
	if (pressed && counter == 5) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 6) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.0f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 7) {
		player->velocity.x = 0.f;
		player->velocity.y = -0.01f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 8) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
	}

	if (counter == 11) {
		counter = 0;
	} else {
		counter++;
	}
	if (timer) {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
	} else {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	}
}
void BlockFly::onTick(C_GameMode* gm) {
}

void BlockFly::onDisable() {
	auto blinkMod = moduleMgr->getModule<Scaffold>();
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	blinkMod->spoof = true;
	if (safe) {
		// hi :)
	} else {
		if (blinkMod->isEnabled()) {
			blinkMod->setEnabled(false);
		}
	}
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
}