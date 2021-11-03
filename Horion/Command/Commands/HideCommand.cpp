#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("[%sNG%s] %sHidden.", GOLD, WHITE, LIGHT_PURPLE);
	} else {
		clientMessageF("[%sNG%s] %sMod is now visible.", GOLD, WHITE, LIGHT_PURPLE);
	}
	return true;
}
