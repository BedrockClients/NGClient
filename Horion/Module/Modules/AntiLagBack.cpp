#include "AntiLagBack.h"

AntiLagBack::AntiLagBack() : IModule(0, Category::PLAYER, "Cancel SetPos, aka cancel's getting lagbacked") {
}

AntiLagBack::~AntiLagBack() {
}

const char* AntiLagBack::getModuleName() {
	return "AntiLagBack";
}