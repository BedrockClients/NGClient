#include "InventoryView.h"
#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Module/ModuleManager.h"
#include "../ModuleManager.h"

InventoryView::InventoryView() : IModule(0x0, Category::GUI, "renders inventory on screen") {
	registerFloatSetting("invPosX", &invX, invX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("invPosY", &invY, invY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
}

InventoryView::~InventoryView() {
}

const char* InventoryView::getModuleName() {
	return ("InventoryView");
}

void InventoryView::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		C_PlayerInventoryProxy* supplies2 = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv2 = supplies2->inventory;
		g_Data.getLocalPlayer()->getSupplies()->inventory;
		float sideBars = 1.5f;
		float yVal = invY + sideBars;

		xVal = invX + sideBars;

		static float rcolors[4];
		static auto hud = moduleMgr->getModule<HudModule>();
		if (hud->rgb) {
			if (rcolors[3] < 1) {
				rcolors[0] = 1;
				rcolors[1] = 0.2f;
				rcolors[2] = 0.2f;
				rcolors[3] = 1;
			}
			
			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			
			rcolors[0] += 0.0015f;
			if (rcolors[0] >= 1) {
				rcolors[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);
		} else {
			//tobo
			DrawUtils::setColor(255, 255, 255, 1.f);
			//
		}
		DrawUtils::drawRectangle(vec2_t(invX, invY), vec2_t(invX + 150.f + sideBars, invY + 60.f + sideBars), sideBars / 2);

		for (int j = 9; j < 18; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal, yVal + 0.f), 1.f, 1.f - .30f, false);
				char stackAmount = inv2->getItemStack(j)->count;
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 6.5f, (yVal + 0.f) + 9.5f), &stackStr, MC_Color(0, 0, 0), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 18; j < 27; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal + 27.f, yVal + 20.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 33.5f, (yVal + 20.f) + 9.5f), &stackStr, MC_Color(0, 0, 0), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 27; j < 36; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal + 54.f, yVal + 40.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 60.5f, (yVal + 40.f) + 9.5f), &stackStr, MC_Color(0, 0, 0), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
	}
}