#pragma once
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
	AntiBot();
	~AntiBot();

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

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
