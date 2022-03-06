#pragma once
#include "Module.h"
class ServerInfo : public IModule {
public:
	ServerInfo();
	~ServerInfo();

	float scale = 1.f;
	float serverInfoX = 210.f;
	float serverInfoY = 25.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};