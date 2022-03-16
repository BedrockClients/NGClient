#include "../../../SDK/Tag.h"
#include "Partner.h"

Partner::Partner() : IModule(0, Category::PARTNER, "Partnered Clients") {

	registerEnumSetting("Partnered Types", &Partnered, 0);
	Partnered = (*new SettingEnum(this))
					.addEntry(EnumEntry("Surge", 0))
					.addEntry(EnumEntry("Fadeaway", 1))
					.addEntry(EnumEntry("NG", 2));
				    //.addEntry(EnumEntry("Weather", 3));
}
Partner::~Partner() {
}
const char* Partner::getModuleName() {
		return "Partner";
}