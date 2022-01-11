#pragma once
//#include "Tag.h"
#include <memory>
#include "TextHolder.h"
#include "../Utils/HMath.h"

class CompoundTag;
class Tag;
class C_BlockLegacy;
class C_BlockSource;
class C_Block;
class C_Entity;
class C_ItemStack;
class C_ScreenContext;
class C_ItemRenderer;
class C_ClientInstance;
class MinecraftGame;

class C_BaseActorRenderContext {
private:
	char pad_0x0[0x60];  //0x0000
public:
	C_ItemRenderer* renderer;  //0x0058
private:
	char pad_0x50[0x238];  //0x60
public:
	C_BaseActorRenderContext(C_ScreenContext* ScreenCtx, C_ClientInstance* client, MinecraftGame* game);
};

class C_ItemRenderer {
public:
	void renderGuiItemNew(C_BaseActorRenderContext* BaseActorRenderCtx, C_ItemStack* item, MinecraftGame* game, float x, float y, float opacity, float scale, bool isEnchanted);
	void renderGuiItemInChunk(C_BaseActorRenderContext* BaseActorRenderCtx, C_ItemStack* item, float x, float y, float opacity, float scale, bool isEnchanted, int mode);
};


class C_Player;
class C_ItemStack;
class PointingStruct;

class C_Item {
	char pad_0008[0x70];     //0x0008
public:
	int16_t maxStackSize;   //0x0090
	int16_t itemId;         //0x0092
private:
	char pad_0094[4];       //0x0094
public:
	TextHolder tileName;    //0x0098
private:
	char pad_00B8[8];       //0x00B8
public:
	TextHolder name;        //0x00C0
private:
	char pad_00E0[8];       //0x00E0
public:
	TextHolder isFrom;		//0x00E8
private:
	char pad_0108[80];      //0x0108
public:
	int16_t duration;       //0x0158

private:
	virtual void destructor();                                                                                    // 0
	virtual __int64 initServer(__int64, __int64);                                                // 1
	virtual __int64 tearDown(void);                                                                               // 2
public:
	virtual __int64 getMaxUseDuration(C_ItemStack const *);                                                      // 3
	virtual __int64 getMaxUseDuration(C_ItemStack const *) const;                                                         // 4
	virtual bool isMusicDisk(void);                                                                               // 5
	virtual __int64 executeEvent();                           // 6
	virtual bool isComponentBased(void);                                                                          // 7
	virtual bool isArmor(void);                                                                                   // 8
	virtual bool isBlockPlanterItem(void);                                                                        // 9
	virtual bool isBucket(void);                                                                                  // 10
	virtual bool isCamera(void);                                                                                  // 11
	virtual bool isCandle(void);                                                                                  // 12
	virtual bool isDamageable(void);                                                                              // 13
	virtual bool isDyeable(void);                                                                                 // 14
	virtual bool isDye(void);                                                                                     // 15
	virtual __int64 getItemColor(void);                                                                           // 16
	virtual bool isFertilizer(void);                                                                              // 17
	virtual bool isFood(void);                                                                                    // 18
	virtual bool isThrowable(void);                                                                               // 19
	virtual bool isUseable(void);                                                                                 // 20
	virtual __int64 getComponent(TextHolder const &);                                                           // 21
	virtual __int64 getCamera(void);                                                                              // 22
	virtual __int64 getFood(void);                                                                                // 23
	virtual __int64 getFuel(void);                                                                                // 24
	virtual __int64 setMaxStackSize(unsigned char);                                                                       // 25
	virtual __int64 setStackedByData(bool);                                                                       // 26
	virtual __int64 setMaxDamage(int);                                                                            // 27
	virtual __int64 setHandEquipped(void);                                                                        // 28
	virtual __int64 setUseAnimation(int);                                                                // 29
	virtual __int64 setMaxUseDuration(int);                                                                       // 30
	virtual __int64 setRequiresWorldBuilder(bool);                                                                // 31
	virtual __int64 setExplodable(bool);                                                                          // 32
	virtual __int64 setFireResistant(bool);                                                                       // 33
	virtual __int64 setIsGlint(bool);                                                                             // 34
	virtual __int64 setShouldDespawn(bool);                                                                       // 35
	virtual __int64 getBlockShape(void);                                                                          // 36
	virtual bool canBeDepleted(void);                                                                             // 37
	virtual bool canDestroySpecial(C_Block const &);                                                                // 38
	virtual __int64 getLevelDataForAuxValue(int);                                                                 // 39
	virtual bool isStackedByData(void);                                                                           // 40
	virtual __int64 getMaxDamage(void);                                                                           // 41
	virtual __int64 getAttackDamage(void);                                                                        // 42
	virtual bool isHandEquipped(void);                                                                            // 43
	virtual bool isGlint(C_ItemStack const &);                                                                    // 44
	virtual bool isPattern(void);                                                                                 // 45
	virtual __int64 getPatternIndex(void);                                                                        // 46
	virtual __int64 showsDurabilityInCreative(void);                                                              // 47
	virtual bool isWearableThroughLootTable(CompoundTag const *);                                                 // 48
	virtual bool canDestroyInCreative(void);                                                                      // 49
	virtual bool isDestructive(int);                                                                              // 50
	virtual bool isLiquidClipItem(int);                                                                           // 51
	virtual __int64 shouldInteractionWithBlockBypassLiquid(C_Block const &);                                        // 52
	virtual __int64 requiresInteract(void);                                                                       // 53
	virtual __int64 appendFormattedHovertext(C_ItemStack const &, PointingStruct&, std::string &, bool);                // 54
	virtual bool isValidRepairItem();        // 55
	virtual __int64 getEnchantSlot(void);                                                                         // 56
	virtual __int64 getEnchantValue(void);                                                                        // 57
	virtual __int64 getArmorValue(void);                                                                          // 58
	virtual bool isComplex(void);                                                                                 // 59
	virtual bool isValidAuxValue(int);                                                                            // 60
	virtual __int64 getDamageChance(int);                                                                         // 61
	virtual __int64 getViewDamping(void);                                                                         // 62
	virtual __int64 uniqueAuxValues(void);                                                                        // 63
	virtual bool isActorPlacerItem(void);                                                                         // 64
	virtual bool isMultiColorTinted(C_ItemStack const &);                                                         // 65
	virtual __int64 getColor();                                        // 66
	virtual bool hasCustomColor(C_ItemStack const &);                                                             // 67
	virtual bool hasCustomColor(CompoundTag const *);                                                             // 68
	virtual __int64 clearColor(C_ItemStack &);                                                                    // 69
	virtual __int64 clearColor(CompoundTag *);                                                                    // 70
	virtual __int64 setColor();                                                  // 71
	virtual __int64 getBaseColor(C_ItemStack const &);                                                            // 72
	virtual __int64 getSecondaryColor(C_ItemStack const &);                                                       // 73
	virtual __int64 getActorIdentifier(C_ItemStack const &);                                                      // 74
	virtual __int64 saveAdditionalData(C_ItemStack const &, CompoundTag &);                                       // 75
	virtual __int64 readAdditionalData(C_ItemStack &, CompoundTag const &);                                       // 76
	virtual __int64 buildIdAux(short, CompoundTag const *);                                                       // 77
	virtual bool canUseOnSimTick(void);                                                                           // 78
	virtual __int64 use(C_ItemStack &, C_Player &);                                                                 // 79
	virtual __int64 dispense(C_BlockSource &, __int64, int, vec3_t const &, unsigned char);                               // 80
	virtual __int64 useTimeDepleted(C_ItemStack &, PointingStruct *, C_Player *);                                   // 81
	virtual __int64 releaseUsing(C_ItemStack &, C_Player *, int);                                                 // 82
	virtual __int64 getDestroySpeed(C_ItemStack const &, C_Block const &);                                          // 83
	virtual __int64 hurtActor(C_ItemStack &, C_Entity &, C_Entity &);                                             // 84
	virtual __int64 hitActor(C_ItemStack &, C_Entity &, C_Entity &);                                              // 85
	virtual __int64 hitBlock(C_ItemStack &, C_Block const &, vec3_ti const &, C_Entity &);                        // 86
	virtual __int64 mineBlock(C_ItemStack &, C_Block const &, int, int, int, C_Entity *);                         // 87
	virtual __int64 mineBlock(C_ItemStack &, C_Block const &, int, int, int, C_Entity *) const;                         // 88
	virtual __int64 buildDescriptionName(C_ItemStack const &);                                                    // 89
	virtual __int64 buildDescriptionId(class ItemDescriptor const *, CompoundTag const *);                              // 90
	virtual __int64 buildEffectDescriptionName(C_ItemStack const &);                                              // 91
	virtual __int64 buildCategoryDescriptionName(void);                                                           // 92
	virtual __int64 readUserData(C_ItemStack &, __int64, __int64);                                                // 93
	virtual __int64 writeUserData(C_ItemStack const &, __int64);                                            // 94
	virtual __int64 getMaxStackSize(class ItemDescriptor const *);                                                      // 95
	virtual __int64 inventoryTick(C_ItemStack &, PointingStruct &, C_Entity &, int, bool);                        // 96
	virtual __int64 refreshedInContainer(C_ItemStack const &, PointingStruct &);                                  // 97
	virtual __int64 getCooldownType(void);                                                                        // 98
	virtual __int64 getCooldownTime(void);                                                                        // 99
	virtual __int64 fixupCommon(C_ItemStack &);                                                                   // 100
	virtual __int64 fixupCommon(C_ItemStack &, PointingStruct &);                                                          // 101
	virtual __int64 getDamageValue(CompoundTag const *);                                                          // 102
	virtual __int64 setDamageValue(C_ItemStack &, short);                                                       // 103
	virtual __int64 getInHandUpdateType(C_Player const &, C_ItemStack const &, C_ItemStack const &, bool, bool);  // 104
	virtual __int64 getInHandUpdateType(C_Player const &, C_ItemStack const &, C_ItemStack const &, bool, bool, __int64 fakeuseotherone);  // 105
	virtual __int64 validFishInteraction(int);                                                                    // 106
	virtual bool isSameItem(C_ItemStack const &, C_ItemStack const &);                                            // 107
	virtual __int64 initClient();                                                // 108
	virtual __int64 getInteractText(C_Player const &);                                                            // 109
	virtual __int64 getAnimationFrameFor(C_Entity *, bool, C_ItemStack const *, bool);                                 // 110
	virtual bool isEmissive(int);                                                                                 // 111
	virtual __int64 getLightEmission(int);                                                                        // 112
	virtual __int64 getIcon(C_ItemStack const &, int, bool);                                                      // 113
	virtual __int64 getIconYOffset(void);                                                                         // 114
	virtual __int64 setIcon(const std::string &, int);                                                            // 115
	virtual __int64 setIcon();                                                      // 116
	virtual __int64 setIconAtlas(const std::string &, int);                                                       // 117
	virtual bool canBeCharged(void);                                                                              // 118
	virtual __int64 playSoundIncrementally(C_ItemStack const &, C_Entity &);                                           // 119
	virtual __int64 playSoundIncrementally(C_ItemStack const &, C_Entity &) const;                                           // 120
	virtual __int64 getFurnaceBurnIntervalMultipler(C_ItemStack const &);                                         // 121
	virtual __int64 getFurnaceXPmultiplier(C_ItemStack const &);                                                  // 122
	virtual __int64 getAuxValuesDescription(void);                                                                // 123
	virtual __int64 _checkUseOnPermissions(C_Entity &, C_ItemStack &, unsigned char const &, vec3_ti const &);    // 124
	virtual __int64 _calculatePlacePos(C_ItemStack &, C_Entity &, unsigned char &, vec3_ti &);                            // 125
	virtual __int64 _useOn(C_ItemStack &, C_Entity &, vec3_ti, unsigned char, float, float, float);                              // 126
	virtual __int64 getArmorKnockbackResistance(void);                                                            // 127


public:
	bool isTool(void) {
		if (getAttackDamage() > 0) return true;           // Does Attack Damage
		if (name.getText() == "flint_and_steel") return true;                   // Flint_n_Steel
		if (name.getText() == "compas") return true;                   // Compas
		if (name.getText() == "ender_pearl") return true;                   // Ender_Pearl
		if (name.getText() == "heart_of_the_sea") return true;                   // Heart_of_the_sea
		if (name.getText() == "dragon_breath") return true;                   // dragon_breath
		if (name.getText() == "paper") return true;                   // Paper
		if (name.getText() == "totem") return true;                   // Totem
		if (name.getText() == "emerald") return true;                   // Emerald
		if (name.getText() == "diamond") return true;                   // diamond
		if (name.getText() == "gold") return true;                   // gold
		if (name.getText() == "nametag") return true;                   // Nametag
		if (name.getText() == "enchanted_book") return true;                   // enchanted_book
		if (name.getText() == "nautilus_shell") return true;                   // nautilus_shell
		return false;
	}
	bool isWeapon(void) {
		if (name.getText() == "wooden_sword") return true;  //wooden_sword
		if (name.getText() == "stone_sword") return true;  //stone_sword
		if (name.getText() == "gold_sword") return true;  //gold_sword
		if (name.getText() == "iron_sword") return true;  //iron_sword
		if (name.getText() == "diamond_sword") return true;  //diamond_sword
		if (name.getText() == "netherite_sword") return true;  //netherite_sword
		if (name.getText() == "wooden_axe") return true;  //wooden_axe
		if (name.getText() == "stone_axe") return true;  //stone_axe
		if (name.getText() == "gold_axe") return true;  //gold_axe
		if (name.getText() == "iron_axe") return true;  //iron_axe
		if (name.getText() == "diamond_axe") return true;  //diamond_axe
		if (name.getText() == "netherite_axe") return true;  //netherite_axe
		return false;
	}
	bool isShooter(void) {
		if (name.getText() == "bow" || name.getText() == "crossbow" || name.getText() == "arrow" || name.getText() == "tipped_arrow") return true;  // Bow, crossbows, arrows, tipped arrows
		return false;
	}
	bool isPickaxe(void) {
		if (name.getText() == "wooden_pickaxe") return true;  //wooden_pickaxe
		if (name.getText() == "stone_pickaxe") return true;  //stone_pickaxe
		if (name.getText() == "gold_pickaxe") return true;  //gold_pickaxe
		if (name.getText() == "iron_pickaxe") return true;  //iron_pickaxe
		if (name.getText() == "diamond_pickaxe") return true;  //diamond_pickaxe
		if (name.getText() == "netherite_pickaxe") return true;  //netherite_pickaxe
		return false;
	}
	bool isShovel(void) {
		if (name.getText() == "wooden_shovel") return true;  //wooden_shovel
		if (name.getText() == "stone_shovel") return true;  //stone_shovel
		if (name.getText() == "gold_shovel") return true;  //gold_shovel
		if (name.getText() == "iron_shovel") return true;  //iron_shovel
		if (name.getText() == "diamond_shovel") return true;  //diamond_shovel
		if (name.getText() == "netherite_shovel") return true;  //netherite_shovel
		return false;
	}

	bool isBlock(void) {
		auto val = *reinterpret_cast<__int64***>(reinterpret_cast<__int64>(this) + 0x1A0);
		return val != nullptr && *val != nullptr;
	}
};


class ItemDescriptor {
private:
	char pad_0x0[0x48]; //0x0000
public:
	ItemDescriptor() {
		memset(this, 0x0, sizeof(ItemDescriptor));
	}
	ItemDescriptor(int id, int16_t itemData);
};

class C_ItemStack {
private:
	uintptr_t** vTable;  //0x0000
public:
	C_Item** item;  //0x08
	CompoundTag* tag;  //0x10
private:
	char pad_0x18[0xA]; //0x18
public:
	char count;  //0x22
private:
	char pad_0x1B[0x6D];  //0x23
public:
	C_ItemStack() {
		memset(this, 0x0, sizeof(C_ItemStack));
	}

	C_ItemStack(C_BlockLegacy& legacy, int count) {
		memset(this, 0x0, sizeof(C_ItemStack));
		reinit(legacy, count);
	}

	C_ItemStack(C_Item& item, int count, int itemData) {
		memset(this, 0x0, sizeof(C_ItemStack));
		reinit(item, count, itemData);
	}

	C_ItemStack(C_ItemStack const& src);

	C_ItemStack(Tag const& tag);

	void fromTag(Tag const& tag);

	void save(CompoundTag** tag);

	void setUserData(std::unique_ptr<Tag> tag);

	bool isValid() {
		return this->item != nullptr && *this->item != nullptr;
	}

	inline C_Item* getItem() {
		return *this->item;
	}

	void reinit(C_BlockLegacy& legacy, int count);

	void reinit(C_Item& item, int count, int itemData);

	int getEnchantValue(int enchantId);

	bool isEnchanted() {
		int enchantValue = 0;
		for (int i = 0; i < 40; i++) {
			enchantValue = this->getEnchantValue(i);
		}
		if (enchantValue != 0)
			return true;
		else
			return false;
	}

	float getArmorValueWithEnchants() {
		if (!this->item || !(*this->item)->isArmor())
			return 0;

		return (float)(((*this->item)->getArmorValue() + ((this->getEnchantValue(0) * 1.5f		// Protection
														   + this->getEnchantValue(5) * 0.4f	// Thorns
														   + this->getEnchantValue(3) * 0.4f	// Blast Protection
														   + this->getEnchantValue(1) * 0.4f	// Fire Protection
														   + this->getEnchantValue(4) * 0.4f	// Projectile Protection
			))));
	}

	float getAttackingDamageWithEnchants() {
		if (!this->item)
			return 0;
		int sharpnessValue = this->getEnchantValue(9);
		return (*this->item)->getAttackDamage() + 1.25f * sharpnessValue;
	}

	void setShowPickUp(bool b) {
		*(bool*)(reinterpret_cast<__int64>(this)+ 0x30) = b;
	}

	void setCustomLore(std::string customLore);

private:
	inline void setVtable(void);
};

class C_ArmorItem : public C_Item {
private:
	char pad_0x108[0x228 - sizeof(C_Item)];  //0x100
public:
	int ArmorSlot;  //0x1B8

	bool isHelmet() {
		return ArmorSlot == 0;
	}
	bool isChestplate() {
		return ArmorSlot == 1;
	}
	bool isLeggings() {
		return ArmorSlot == 2;
	}
	bool isBoots() {
		return ArmorSlot == 3;
	}
};


class ItemRegistry {
public:
	static C_Item ***getItemFromId(void *ptr, int itemId);
	static C_Item*** lookUpByName(void*, void*, TextHolder&);
};
