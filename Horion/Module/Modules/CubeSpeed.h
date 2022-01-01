#include "Module.h"

class CubeSpeed : public IModule {
private:
	int delay = 0;
	int delay2 = 0;
	bool isBypass = false;
	float speedMod = 0.70f;

public:
	virtual void onMove(C_MoveInputHandler* input) override {
		auto player = g_Data.getLocalPlayer();
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		float yaw = player->yaw;

		bool pressed = input->forward || input->backward || input->right || input->left;

		if (input->forward && input->backward)
			return;

		if (!isBypass) {
			if (input->right) {
				yaw += 90.f;
				if (input->forward)
					yaw -= 45.f;
				else if (input->backward)
					yaw += 45.f;
			}
			if (input->left) {
				yaw -= 90.f;
				if (input->forward)
					yaw += 45.f;
				else if (input->backward)
					yaw -= 45.f;
			}

			if (input->backward && !input->left && !input->right)
				yaw += 180.f;

			if (localPlayer->onGround == true && GameData::canUseMoveKeys() && localPlayer->velocity.squaredxzlen() > 0.001f) {
				delay++;
				float calcYaw = (yaw + 90) * (PI / 180);
				vec3_t moveVec;
				moveVec.x = cos(calcYaw) * speedMod;
				moveVec.y = player->velocity.y = 0.035f;
				moveVec.z = sin(calcYaw) * speedMod;
				if (pressed) player->lerpMotion(moveVec);
				if (delay == 2) {
					float calcYaw = (yaw + 90) * (PI / 180);
					vec3_t moveVec;
					localPlayer->velocity.x = 0.0;
					localPlayer->velocity.z = 0.0;
					localPlayer->velocity.y = 0.0;
					if (pressed) player->lerpMotion(moveVec);
					delay = 0;
				}
			}
		} else {
			if (input->right) {
				yaw += 90.f;
				if (input->forward)
					yaw -= 45.f;
				else if (input->backward)
					yaw += 45.f;
			}
			if (input->left) {
				yaw -= 90.f;
				if (input->forward)
					yaw += 45.f;
				else if (input->backward)
					yaw -= 45.f;
			}

			if (input->backward && !input->left && !input->right)
				yaw += 180.f;
			float calcYaw = (yaw + 90) * (PI / 180);

			if (GameData::canUseMoveKeys() && localPlayer->velocity.squaredxzlen() > 0.001f) {
				delay2++;
				vec3_t moveVec;
				moveVec.x = cos(calcYaw) * speedMod;
				moveVec.z = sin(calcYaw) * speedMod;

				player->lerpMotion(moveVec);
				if (delay2 == 2) {
					vec3_t moveVec;
					moveVec.x = cos(calcYaw) * 0;
					moveVec.z = sin(calcYaw) * 0;
					player->lerpMotion(moveVec);
					delay2 = 0;
				}
			}
		}
	}
	virtual void onDisable() override {
		g_Data.getLocalPlayer()->velocity.x = 0;
		g_Data.getLocalPlayer()->velocity.y = 0;
		g_Data.getLocalPlayer()->velocity.z = 0;
	}
	C_MovePlayerPacket* jetpack = nullptr;
	CubeSpeed() : IModule(0x0, Category::SERVER, "Speed bypass for CubeCraft") {
		registerFloatSetting("speed", &speedMod, 1, 0.3f, 2.5f);
		registerBoolSetting("Fly", &isBypass, isBypass);
	}
	~CubeSpeed(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("CubeSpeed"); }
};