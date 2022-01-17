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

//f3 0f 11 54 24 ? 41 0f 28 d8 f3 0f 10 0d ? ? ? ? e8
//41 0f 28 d8 f3 0f 10 0d ? ? ? ? e8 ? ? ? ? c6 47
//nop these 2 and get real blochhit
void SwingAnimations::onEnable() {
	//Floppy
	if (floppySwing) {
		targetAddress2 = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		Utils::nopBytes((BYTE*)targetAddress2, 8);
		Utils::nopBytes((BYTE*)targetAddress, 4);
	}

	//Flux
	if (fluxSwing) {
		targetAddress = (void*)FindSignature("e8 ? ? ? ? f3 0f 10 0d ? ? ? ? 41 0f 28 c0");
		Utils::nopBytes((BYTE*)targetAddress, 5);
	}

	//NoObstruct
	if (noObstructSwing) {
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		Utils::nopBytes((BYTE*)targetAddress, 4);
	}

	//PushSwing
	if (pushSwing) {
		targetAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		targetAddress2 = (void*)FindSignature("F3 ? ? C1 ? ? C8 48 8D 15");
		Utils::nopBytes((BYTE*)targetAddress, 4);
		Utils::nopBytes((BYTE*)targetAddress2, 4);
	}

	//Java
	if (fakeJavaSwing) {
		targetAddress = (void*)FindSignature("0F 28 F8 F3 0F 59 3D ? ? ? ? C6 47");
		Utils::nopBytes((BYTE*)targetAddress, 3);
	}

}

void SwingAnimations::onDisable() {
	//Floppy
	if (floppySwing) {
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B", 8);
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);
	}
	
	//Flux
	if (fluxSwing)
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xE8\xC7\xF4\x3B\xFF\xF3\x0F\x10\x0D\x03\x32\x30\x02\x41\x0F\x28\xC0", 8);

	//NoObstruct
	if (noObstructSwing)
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);

	//PushSwing
	if (pushSwing) {
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress2), (BYTE*)"\xF3\x0F\x2C\xC1", 4);
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);
	}

	//Java
	if (fakeJavaSwing)
		Utils::patchBytes((BYTE*)((uintptr_t)targetAddress), (BYTE*)"\x0F\x28\xF8\xF3", 3);
}