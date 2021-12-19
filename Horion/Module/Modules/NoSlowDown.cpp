#include "NoSlowDown.h"

#include <Windows.h>

#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"

NoSlowDown::NoSlowDown() : IModule(0, Category::MOVEMENT, "Don't get slowed down when blocking or eating") {
}

NoSlowDown::~NoSlowDown() {
}

const char* NoSlowDown::getModuleName() {
	return ("NoSlowDown");
}

static void changeBytes(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void NoSlowDown::onEnable() {
	if (targetAddress == nullptr)
		targetAddress = (void*)FindSignature("F3 0F 11 46 0C 41 C7");
	BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90";
	changeBytes((BYTE*)((uintptr_t)targetAddress), patch, 5);

	if (targetAddress2 == nullptr)
		targetAddress2 = (void*)FindSignature("F3 0F 11 46 0C F3 0F 10 05");
	BYTE* patch2 = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90";
	changeBytes((BYTE*)((uintptr_t)targetAddress2), patch2, 3);
}

void NoSlowDown::onDisable() {
	BYTE* patch = (BYTE*)"\xF3\x0F\x11\x46\x0C\x41\xC7";
	changeBytes((BYTE*)((uintptr_t)targetAddress), patch, 5);
	BYTE* patch2 = (BYTE*)"\xF3\x0F\x11\x46\x0C\xF3\x0F\x10\x05";
	changeBytes((BYTE*)((uintptr_t)targetAddress2), patch2, 3);
}
