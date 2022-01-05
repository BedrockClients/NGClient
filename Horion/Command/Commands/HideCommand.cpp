#include "HideCommand.h"
#include "../../Module/ModuleManager.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	static auto Surge = moduleMgr->getModule<HudModule>();
	GameData::hide();
	if (GameData::shouldHide()) {
		if (Surge->surge)
		clientMessageF("[%sSurge%s] %sHidden.", GOLD, WHITE, BLUE);
		else
			clientMessageF("[%sNG%s] %sHidden.", GOLD, WHITE, LIGHT_PURPLE);
	} else {
		if (Surge->surge)
		clientMessageF("[%sSurge%s] %sMod is now visible.", GOLD, WHITE, BLUE);
		else
		clientMessageF("[%sNG%s] %sMod is now visible.", GOLD, WHITE, LIGHT_PURPLE);
	}
	return true;
}
