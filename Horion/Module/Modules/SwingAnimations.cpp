#include "SwingAnimations.h"

SwingAnimations::SwingAnimations() : IModule(0, Category::VISUAL, "SwingAnimations. Simple As That") {
	registerBoolSetting("FloppySwing", &floppySwing, floppySwing);
	registerBoolSetting("FluxSwing", &fluxSwing, fluxSwing);
	registerBoolSetting("NoObstructSwing", &noObstructSwing, noObstructSwing);
	registerBoolSetting("PushSwing", &pushSwing, pushSwing);
	registerBoolSetting("FakeJavaSwing", &fakeJavaSwing, fakeJavaSwing);
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
	//Floppy
	if (floppySwing) {
		targetAddress2 = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		Nop3((BYTE*)targetAddress2, 8);
		Nop3((BYTE*)targetAddress, 4);
	}

	//Flux
	if (fluxSwing) {
		targetAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
		Nop3((BYTE*)targetAddress, 8);
	}

	//NoObstruct
	if (noObstructSwing) {
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		Nop3((BYTE*)targetAddress, 4);
	}

	//PushSwing
	if (pushSwing) {
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		targetAddress2 = (void*)FindSignature("F3 ? ? C1 ? ? C8 48 8D 15");
		Nop3((BYTE*)targetAddress, 4);
		Nop3((BYTE*)targetAddress2, 4);
	}

	//Java
	if (fakeJavaSwing) {
		targetAddress = (void*)FindSignature("0F 28 F8 F3 0F 59 3D ? ? ? ? C6 47");
		Nop3((BYTE*)targetAddress, 3);
	}

}

void SwingAnimations::onDisable() {
	//Floppy
	if (floppySwing) {
		Patch3((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B", 8);
		Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);
	}

	//Flux
	if (fluxSwing)
		Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B", 8);

	//NoObstruct
	if (noObstructSwing)
		Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);

	//PushSwing
	if (pushSwing) {
		Patch3((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\xF3\x0F\x2C\xC1", 4);
		Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);
	}

	//Java
	if (fakeJavaSwing)
		Patch3((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x28\xF8\xF3", 3);
}