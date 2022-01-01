#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class TestModule : public IModule {
public:
	TestModule() : IModule(0x0, Category::WORLD, "For testing purposes"){};
	~TestModule(){};

	void onEnable() {
	}

	void onTick(C_GameMode* gm) {
	}

	void onMove(C_MoveInputHandler* hand) {
	}

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	}

	void onSendPacket(C_Packet* packet) {
	}

	void onDisable() {
	}

	void onLevelRender() {
	}

	void onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	}

	virtual const char* getModuleName() override {
		return "TestModule";
	}
};