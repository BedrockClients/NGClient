#include "ServerInfo.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

ServerInfo::ServerInfo() : IModule(0x0, Category::GUI, "shows the server ip and port of the current server") {
	registerFloatSetting("ServerX", &serverInfoX, serverInfoX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("ServerY", &serverInfoY, serverInfoY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

ServerInfo::~ServerInfo() {
}

const char* ServerInfo::getModuleName() {
	return ("ServerInfo");
}

static float currColor[4];

void ServerInfo::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	// rainbow colors
	{
		if (currColor[3] < 1) {
			currColor[0] = 1;
			currColor[1] = 0.2f;
			currColor[2] = 0.2f;
			currColor[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
	}

	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.getLocalPlayer() != nullptr || g_Data.getRakNetInstance()->isonaServer()) {
			auto Server = g_Data.getRakNetInstance();
			if (Server == nullptr) return;

			float yVal = serverInfoY;
			float xVal = serverInfoX;

			std::string IP = Server->serverIp.getText();
			std::string Port = std::to_string(Server->serverPort).c_str();

			vec2_t textPos = vec2_t(xVal, yVal);

			if (Server->serverIp.getTextLength() < 1) {
				IP = "Local World";
			}
			std::string ServerText = "IP: " + IP + " \nPort: " + Port;

			static auto hud = moduleMgr->getModule<HudModule>();
			if (hud->rgb) {
				DrawUtils::drawText(vec2_t{textPos}, &ServerText, MC_Color(currColor), scale);
			} else if (hud->surge) {
				DrawUtils::drawText(vec2_t{textPos}, &ServerText, MC_Color(0, 0, 255), scale);
			} else {
				DrawUtils::drawText(vec2_t{textPos}, &ServerText, MC_Color(184, 0, 255), scale);
			}
		}
	}
}