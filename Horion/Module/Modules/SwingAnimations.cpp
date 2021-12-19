#include "SwingAnimations.h"
#include "TestModule.h"

#include <array>
#include <deque>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_transform.hpp>  // perspective, translate, rotate
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>  //radians
#include <unordered_set>
#include "../../../SDK/MatrixStack.h"
#include "../../../Utils/Json.hpp"
#include "../../../Utils/Logger.h"
#include "../../../Utils/VoxelIntersector.h"
#include "../../DrawUtils.h"

SwingAnimations::SwingAnimations() : IModule(0, Category::VISUAL, "Don't get slowed down when blocking or eating") {
	registerEnumSetting("Swing Type", &setting, 0);
	setting = SettingEnum()
				  //.addEntry(EnumEntry("8Bit Swing", 0))
				  .addEntry(EnumEntry("Floppy Swing", 0))
				  .addEntry(EnumEntry("Flux Swing", 1))
				  .addEntry(EnumEntry("NoObstruct Swing", 2))
				  .addEntry(EnumEntry("Push Swing", 3));
}

SwingAnimations::~SwingAnimations() {
}

const char* SwingAnimations::getModuleName() {
	return ("SwingAnimations");
}

static void changeBytes(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void SwingAnimations::onEnable() {
	//8bitSwing
	/* if (setting.selected == 0) {
		if (eightbitddress == nullptr)
			eightbitddress = (void*)FindSignature("41 ? ? CD 49 8B CF FF 90");
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)eightbitddress), patch, 5);
	}
	*/

	//FloppySwing
	if (setting.selected == 0) {
		if (floppyAddress == nullptr && floppyAddress2 == nullptr) {
			floppyAddress2 = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
			floppyAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		}
		BYTE* patch2 = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)floppyAddress2), patch2, 6);
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)floppyAddress), patch, 4);
	}

	//FluxSwing
	if (setting.selected == 1) {
		if (fluxAddress == nullptr)
			fluxAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)fluxAddress), patch, 6);
	}

	//NoObstructSwing
	if (setting.selected == 2) {
		if (noObstructAddress == nullptr)
			noObstructAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)noObstructAddress), patch, 4);
	}

	//PushSwing
	if (setting.selected == 3) {
		if (pushAddress == nullptr) {
			pushAddress = (void*)FindSignature("F3 ? ? F0 ? ? C8 F3 ? ? C8");
			pushAddress2 = (void*)FindSignature("F3 ? ? C1 ? ? C8 48 8D 15");
		}
		BYTE* patch2 = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)pushAddress2), patch2, 4);
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)pushAddress), patch, 4);
	}

}

void SwingAnimations::onDisable() {
	//8Bit
	/* if (setting.selected == 0) {
		if (eightbitddress == nullptr)
			eightbitddress = (void*)FindSignature("41 ? ? CD 49 8B CF FF 90");
		BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		changeBytes((BYTE*)((uintptr_t)eightbitddress), patch, 5);
	}*/

	//Floppy
	if (setting.selected == 0) {
		BYTE* patch2 = (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B\x46\x40\x48\x85\xC0";
		changeBytes((BYTE*)((uintptr_t)floppyAddress2), patch2, 6);
		BYTE* patch = (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8\xF3\x0F\x59\xC8";  //F3 0F 51 F0 0F 28 C8 F3 0F 59 C8
		changeBytes((BYTE*)((uintptr_t)floppyAddress), patch, 4);
	}

	//Flux
	if (setting.selected == 1) {
		BYTE* patch = (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B\x46\x40\x48\x85\xC0";
		changeBytes((BYTE*)((uintptr_t)fluxAddress), patch, 6);
	}

	//NoObstruction
	if (setting.selected == 2) {
		BYTE* patch = (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8\xF3\x0F\x59\xC8";  //F3 0F 51 F0 0F 28 C8 F3 0F 59 C8
		changeBytes((BYTE*)((uintptr_t)noObstructAddress), patch, 4);
	}

	//Push
	if (setting.selected == 3) {
		BYTE* patch2 = (BYTE*)"\xF3\x0F\x2C\xC1\x0F\xB7\xC8\x48\x8D\x15";  //F3 0F 2C C1 0F B7 C8 48 8D 15
		changeBytes((BYTE*)((uintptr_t)pushAddress2), patch2, 4);
		BYTE* patch = (BYTE*)"\xF3\x0F\x51\xF0\x0F\x28\xC8\xF3\x0F\x59\xC8";  //F3 0F 51 F0 0F 28 C8 F3 0F 59 C8
		changeBytes((BYTE*)((uintptr_t)pushAddress), patch, 4);
	}
}
