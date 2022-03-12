#include "../../../SDK/Tag.h"
#include "Partner.h"

Partner::Partner() : IModule(0, Category::PARTNER, "Partnered Clients") {

	registerEnumSetting("Arraylist Types", &Partnered, 0);
	Partnered = (*new SettingEnum(this))
					.addEntry(EnumEntry("Surge", 0))
					.addEntry(EnumEntry("Fadeaway", 1));
//	Partnered.selected == 0  // Surge
//	Partnered.selected == 1  // Fadeaway
}
Partner::~Partner() {
}
const char* Partner::getModuleName() {
		return "Partner";
}