#include "HiveConfig.h"

#include "../../Module/ModuleManager.h"

HiveConfig::HiveConfig() : IModule(0x0, Category::CONFIG, "Auto Loads Best Config For Hive") {
}

HiveConfig::~HiveConfig() {
}

const char* HiveConfig::getModuleName() {
	return ("Hive");
}

void HiveConfig::onEnable() {
	//Disable All and Unbind All
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		mod->setEnabled(false);
		mod->setKeybind(0x0);
	}

	//Modules
	static auto HudMod = moduleMgr->getModule<HudModule>();
	static auto KillMod = moduleMgr->getModule<Killaura>();
	static auto ESPMod = moduleMgr->getModule<ESP>();
	static auto Stop = moduleMgr->getModule<FastStop>();
	static auto AutoArm = moduleMgr->getModule<AutoArmor>();
	static auto StepBro = moduleMgr->getModule<Step>();
	static auto Sprint = moduleMgr->getModule<AutoSprint>();
	static auto BowBot = moduleMgr->getModule<BowAimbot>();
	static auto Scaff = moduleMgr->getModule<Scaffold>();
	static auto Break = moduleMgr->getModule<InstaBreak>();
	static auto HackerDetector = moduleMgr->getModule<HackerDetect>();
	static auto Fuck = moduleMgr->getModule<Fucker>();
	static auto NoSlow = moduleMgr->getModule<NoSlowDown>();
	static auto ClickGUI = moduleMgr->getModule<ClickGuiMod>();
	static auto ReachMod = moduleMgr->getModule<Reach>();
	static auto Bright = moduleMgr->getModule<FullBright>();
	static auto Web = moduleMgr->getModule<NoWeb>();
	static auto HiveFli = moduleMgr->getModule<HiveFly>();
	static auto JesusSUS = moduleMgr->getModule<Jesus>();
	static auto FastLAd = moduleMgr->getModule<FastLadder>();
	static auto Tags = moduleMgr->getModule<NameTags>();
	static auto Hop = moduleMgr->getModule<Bhop>();
	static auto Mid = moduleMgr->getModule<MidClick>();
	static auto Select = moduleMgr->getModule<selectionHighlight>();
	static auto AntiBotMod = moduleMgr->getModule<AntiBot>();
	static auto Cleaner = moduleMgr->getModule<InventoryCleaner>();
	static auto Team = moduleMgr->getModule<Teams>();
	static auto NoHurt = moduleMgr->getModule<NoHurtcam>();
	static auto AntiImmo = moduleMgr->getModule<AntiImmobile>();
	static auto ViewMod = moduleMgr->getModule<ViewModel>();
	static auto ChestSteal = moduleMgr->getModule<ChestStealer>();
	static auto Disable = moduleMgr->getModule<Disabler>();
	static auto AntiKBMod = moduleMgr->getModule<Antikb>();
	static auto SwingAnimation = moduleMgr->getModule<SwingAnimations>();
	static auto ArrayList = moduleMgr->getModule<GUI>();
	static auto Long = moduleMgr->getModule<LongJump>();

	//Toggle All Needed Mods
	HudMod->setEnabled(true);
	ClickGUI->setEnabled(false);
	AntiBotMod->setEnabled(true);
	Select->setEnabled(true);
	AntiKBMod->setEnabled(true);
	AntiImmo->setEnabled(true);
	HackerDetector->setEnabled(true);
	NoSlow->setEnabled(true);
	ChestSteal->setEnabled(true);
	BowBot->setEnabled(true);
	NoHurt->setEnabled(true);
	AutoArm->setEnabled(true);
	FastLAd->setEnabled(true);
	ViewMod->setEnabled(true);
	Sprint->setEnabled(true);
	Break->setEnabled(true);
	Cleaner->setEnabled(true);
	Tags->setEnabled(true);
	Bright->setEnabled(true);
	Stop->setEnabled(true);
	Mid->setEnabled(true);
	Disable->setEnabled(true);
	Fuck->setEnabled(true);
	Web->setEnabled(true);
	ReachMod->setEnabled(true);
	JesusSUS->setEnabled(true);
	StepBro->setEnabled(true);
	ESPMod->setEnabled(true);
	Team->setEnabled(true);
	SwingAnimation->setEnabled(true);

	//Set All Settings

	//Killaura
	KillMod->setKeybind('F');
	KillMod->range = 6.f;
	KillMod->delay = 0;
	KillMod->rots.selected = 1;
	KillMod->mode.selected = 1;
	KillMod->targ.selected = 0;
	KillMod->info = true;
	KillMod->hurttime = false;
	KillMod->isMobAura = false;
	KillMod->noSwing = false;
	//Scaffold
	Scaff->setKeybind('G');
	Scaff->staircaseMode = true;
	Scaff->fagNigas = true;
	Scaff->UpwardsFlyinNigas = 0.50f;
	Scaff->autoselect = true;
	Scaff->Fullselect = true;
	Scaff->spoof = true;
	Scaff->spam = true;
	Scaff->rot = true;
	Scaff->SukinMyBigJuicyAss = true;
	Scaff->noSwing = true;
	Scaff->yLock = true;
	Scaff->predict = false;
	Scaff->GayNigaFags = true;
	//Bhop
	Hop->setKeybind('C');
	Hop->speed = 0.90;
	Hop->hive = true;
	//Breaker
	Fuck->setKeybind('V');
	Fuck->noSwing = true;
	Fuck->redstone = true;
	Fuck->bypass = true;
	Fuck->rots = false;
	Fuck->treasures = true;
	Fuck->chests = false;
	Fuck->range = 5;
	//Teams
	Team->colorCheck = true;
	//Disabler
	Disable->hive = true;
	//Selection Highlight
	Select->thickness = 0.40f;
	Select->opacityVal = 1.f;
	Select->selectRainbow = false;
	Select->doOutline = true;
	Select->rSelect = 1.f;
	Select->bSelect = 1.f;
	Select->gSelect = 1.f;
	//HiveFly
	HiveFli->setKeybind('R');
	HiveFli->clip = false;
	HiveFli->clipHeight = 5.f;
	//LongJump
	Long->setKeybind('X');
	Long->slow = true;
	Long->hit = true;
	Long->speed = 1.63f;
	Long->height = 0.52f;
	//BowAimbot
	BowBot->predict = true;
	BowBot->visualize = true;
	//Step
	StepBro->height = 2.f;
	//ESP
	ESPMod->betterESP = false;
	ESPMod->circle = false;
	ESPMod->doRainbow = false;
	ESPMod->is2d = false;
	ESPMod->iszephyr = true;
	ESPMod->isMobEsp = false;
	//FullBright
	Bright->intensity = 25.f;
	//NameTags
	Tags->displayArmor = true;
	Tags->underline = true;
	Tags->opacity = .12f;
	//Viewmodel
	ViewMod->xTrans = 0.35f;
	ViewMod->yTrans = 0.06f;
	ViewMod->zTrans = -0.74f;
	ViewMod->doTranslate = true;
	ViewMod->doScale = false;
	ViewMod->doRotation = false;
	ViewMod->spin = false;
	//AutoSprint
	Sprint->alldirections = true;
	//FastLadder
	FastLAd->speed = 0.60f;
	//AntiBot
	AntiBotMod->hitboxCheck = true;
	AntiBotMod->extraCheck = false;
	AntiBotMod->entityIdCheck = true;
	AntiBotMod->nameCheck = true;
	AntiBotMod->otherCheck = false;
	AntiBotMod->invisibleCheck = false;
	//ChestStealer
	ChestSteal->delay = 0;
	ChestSteal->enhanced = true;
	ChestSteal->dump = false;
	//InvCleaner
	Cleaner->setKeybind('N');
	Cleaner->autoSort = true;
	Cleaner->keepArmor = true;
	Cleaner->keepBlocks = true;
	Cleaner->keepBow = false;
	Cleaner->keepFood = true;
	Cleaner->keepPick = false;
	Cleaner->keepShovel = false;
	Cleaner->keepTools = true;
	Cleaner->openInv = false;
	//ClickGUI
	ClickGUI->setKeybind(VK_TAB);
	ClickGUI->showTooltips = true;
	//Arraylist
	ArrayList->different = true;
	ArrayList->Fluxbar = true;
	ArrayList->bar = false;
	ArrayList->underbar = false;
	ArrayList->rgb = true;
	ArrayList->ice = false;
	ArrayList->bottom = false;
	ArrayList->opacity = 0.26f;
	ArrayList->rcolor = 0.f;
	ArrayList->gcolor = 0.f;
	ArrayList->bcolor = 0.f;
	//HUDModule
	HudMod->surge = true;
	HudMod->Hud = true;
	HudMod->rgb = false;
	HudMod->Msg = false;
	HudMod->displayArmor = false;
	HudMod->clickToggle = false;
	HudMod->watermark = true;
	HudMod->notifications = false;
	HudMod->bools = false;
	HudMod->keybinds = true;
	HudMod->keystrokes = false;
	HudMod->displaySecondHalf = false;
	HudMod->alwaysShow = false;
	HudMod->opacity = 0.28f;
	HudMod->scale = 0.75f;
	//InstaBreak
	Break->mode.selected = 1;
	//Swing Animations
	SwingAnimation->fluxSwing = true;

	//Tell User Binds
	g_Data.getGuiData()->displayClientMessageF("=======================================");
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		auto modOpt = mod;
		if (Utils::getKeybindName(mod->getKeybind()) != "Unknown") {
			if (HudMod->surge)
				g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] %s is currently bound to %s", WHITE, BLUE, WHITE, mod->getModuleName(), Utils::getKeybindName(mod->getKeybind()));
			else
				g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] %s is currently bound to %s", WHITE, LIGHT_PURPLE, WHITE, mod->getModuleName(), Utils::getKeybindName(mod->getKeybind()));
		}
	}

	//Success
	if (HudMod->surge) {
		g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Successfully Made Config!", WHITE, BLUE, WHITE, BLUE);
	} else {
		g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Successfully Made Config!", WHITE, LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
	}

	//Tell Dumbass To Save Config
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Type %s.config save%s to save your config!", WHITE, GREEN, WHITE, GREEN, WHITE, GREEN);
}
