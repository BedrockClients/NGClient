#include "SwingAnimations.h"

SwingAnimations::SwingAnimations() : IModule(0, Category::VISUAL, "SwingAnimations. Simple As That") {
	registerBoolSetting("FloppySwing", &floppySwing, floppySwing);
	registerBoolSetting("FluxSwing", &fluxSwing, fluxSwing);
	registerBoolSetting("NoObstructSwing", &noObstructSwing, noObstructSwing);
	registerBoolSetting("PushSwing", &pushSwing, pushSwing);
}

SwingAnimations::~SwingAnimations() {
}

const char* SwingAnimations::getModuleName() {
	return "SwingAnimations";
}

//f3 0f 11 54 24 ? 41 0f 28 d8 f3 0f 10 0d ? ? ? ? e8
//41 0f 28 d8 f3 0f 10 0d ? ? ? ? e8 ? ? ? ? c6 47
//nop these 2 and get real blochhit
void SwingAnimations::onEnable() {
	//Floppy
	if (floppySwing) {
		targetAddress2 = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 56 ? 48 85 D2 74 ? 48 8B 02");
		targetAddress = (void*)FindSignature("F3 0F 51 F0 0F 28 C8");
		Utils::nopBytes((BYTE*)targetAddress2, 8);
		Utils::nopBytes((BYTE*)targetAddress, 4);
	}

	//Flux
	if (fluxSwing) {
		targetAddress = (void*)FindSignature("E8 ? ? ? ? F3 0F 10 0D ? ? ? ? 41 0F 28 C0");
		Utils::nopBytes((BYTE*)targetAddress, 5);
	}

	//NoObstruct
	if (noObstructSwing) {
		targetAddress = (void*)FindSignature("F3 0F 51 F0 0F 28 C8");
		Utils::nopBytes((BYTE*)targetAddress, 4);
	}

	//PushSwing
	if (pushSwing) {
		targetAddress = (void*)FindSignature("F3 0F 51 F0 0F 28 C8");
		targetAddress2 = (void*)FindSignature("F3 ? 2C C1 ? B7 ? 48 8D 15");
		Utils::nopBytes((BYTE*)targetAddress, 4);
		Utils::nopBytes((BYTE*)targetAddress2, 4);
	}

}

void SwingAnimations::onDisable() {
	//Floppy
	if (floppySwing) {
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\x0F\x84\x00\x00\x00\x00\x48\x8B\x56\x00\x48\x85\xD2\x74\x00\x48\x8B\x02", 8);
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8", 4);
	}
	
	//Flux
	if (fluxSwing)
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xE8\x34\x52\x37\xFF", 5);

	//NoObstruct
	if (noObstructSwing)
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8", 4);

	//PushSwing
	if (pushSwing) {
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\xF3\x0F\x2C\xC1\x0F\xB7\xC8\x48\x8D\x15", 4);
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8", 4);
	}
}