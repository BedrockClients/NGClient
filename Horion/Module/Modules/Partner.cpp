#include "../../../SDK/Tag.h"
#include "Partner.h"

Partner::Partner() : IModule(0, Category::PARTNER, "Partnered Clients") {
	registerBoolSetting("Surge", &surge, surge);
	registerBoolSetting("Fadeaway (clickgui)", &fadeaway, fadeaway);
}
Partner::~Partner() {
}
const char* Partner::getModuleName() {
		return "Partner";
}
