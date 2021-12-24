#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	int slot;
	bool airplace = false;
	bool autoselect = true;
	bool entityscaff = false;
	bool predict = true;
	bool yLock = false;
	bool staircaseMode = false;
	bool tryScaffold(vec3_t blockBelow);
	bool findBlock();
	bool rot = false;
	vec3_t blockBelowtest;
	vec3_t blockBelowtest2;

public:
	Scaffold();
	~Scaffold();
	bool spoof = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender();
	virtual void onSendPacket(C_Packet* packet);
};
