#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class SwingAnimations : public IModule {
public:
	void* targetAddress;
	SettingEnum enum1;

	SwingAnimations();
	~SwingAnimations();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onSendPacket(C_Packet* p) override;
	virtual void onMove(C_MoveInputHandler* hand) override;
	virtual void onDisable() override;
	void onLevelRender() override;
};