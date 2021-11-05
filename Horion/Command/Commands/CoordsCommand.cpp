#include "CoordsCommand.h"

#include "../../Module/ModuleManager.h"
CoordsCommand::CoordsCommand() : IMCCommand("coords", "Prints your coordinates", "") {
	registerAlias("pos");
}

CoordsCommand::~CoordsCommand() {
}

bool CoordsCommand::execute(std::vector<std::string>* args) {
	static auto Surge = moduleMgr->getModule<ClickGuiMod>();
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	float yPos = pos->y - 1.62f;
	if (Surge->surge)
	clientMessageF("[%sSurge%s] %sX: %.2f Y: %.2f Z: %.2f", GOLD, WHITE, BLUE, pos->x, yPos /* eye height */, pos->z);
	else
	clientMessageF("[%sNG%s] %sX: %.2f Y: %.2f Z: %.2f", GOLD, WHITE, LIGHT_PURPLE, pos->x, yPos /* eye height */, pos->z);
	return true;
}
