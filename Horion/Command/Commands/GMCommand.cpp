#include "GMCommand.h"

GMCommand::GMCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GMCommand::~GMCommand() {
}

bool GMCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 2) {
		g_Data.getLocalPlayer()->setGameModeType(gamemode);
		clientMessageF("[%sNG%s] %sGamemode Changed!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}

	clientMessageF("[%sNG%s] %sInvalid GameMode!", LIGHT_PURPLE, WHITE, RED);
	return true;
}