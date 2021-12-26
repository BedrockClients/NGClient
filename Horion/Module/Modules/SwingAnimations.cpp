#include "SwingAnimations.h"

using json = nlohmann::json;

SwingAnimations::SwingAnimations() : IModule(0, Category::COMBAT, "SwingAnimations. Simple As That") {
}

SwingAnimations::~SwingAnimations() {
}

const char* SwingAnimations::getModuleName() {
	return "SwingAnimations";
}

void Nop3(BYTE* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Patch3(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void SwingAnimations::onEnable() {
	if (targetAddress == nullptr)
		targetAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");

	Nop3((BYTE*)targetAddress, 8);
}

void SwingAnimations::onTick(C_GameMode* gm) {
}

void SwingAnimations::onMove(C_MoveInputHandler* hand) {
}

void SwingAnimations::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void SwingAnimations::onSendPacket(C_Packet* packet) {
}

void SwingAnimations::onDisable() {
	Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B", 8);
}

void SwingAnimations::onLevelRender() {
}

void SwingAnimations::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}