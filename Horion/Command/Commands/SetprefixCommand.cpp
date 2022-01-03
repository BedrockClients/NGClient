#include "SetprefixCommand.h"

SetprefixCommand::SetprefixCommand() : IMCCommand("setprefix", "Set the prefix for horion commands", "<prefix>") {
	registerAlias("prefix");
}

SetprefixCommand::~SetprefixCommand() {
}

bool SetprefixCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	assertTrue(args->at(1).length() == 1);
	char prefix = args->at(1).at(0);
	cmdMgr->prefix = prefix;
	static auto Surge = moduleMgr->getModule<HudModule>();
	if (Surge->surge)
	clientMessageF("[%sSurge%s] %sSet prefix to %s%c", GOLD, WHITE, BLUE, GRAY, prefix);
	else
		clientMessageF("[%sNG%s] %sSet prefix to %s%c", GOLD, WHITE, LIGHT_PURPLE, GRAY, prefix);
	return true;
}
