#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AntiBot : public IModule {
private:
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;

public:
	bool isHitboxCheckEnabled() {
		return hitboxCheck && isEnabled();
	}
	bool isNameCheckEnabled() {
		return false && isEnabled();
	}
	bool isInvisibleCheckEnabled() {
		return invisibleCheck && isEnabled();
	}
	bool isEntityIdCheckEnabled() {
		return entityIdCheck && isEnabled();
	}
	bool isOtherCheckEnabled() {
		return otherCheck && isEnabled();
	}
	bool isExtraCheckEnabled() {
		return extraCheck && isEnabled();
	}
	AntiBot() : IModule(0x0, Category::PLAYER, "Enable this module to filter bots!") {
		registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
		registerBoolSetting("Name Check", &nameCheck, nameCheck);
		registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
		registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
		registerBoolSetting("Other Check", &otherCheck, otherCheck);
		registerBoolSetting("Extra Check", &extraCheck, extraCheck);
	};
	~AntiBot(){};

	virtual const char* getModuleName() override {
		return "AntiBot";
	}
};
