#pragma once
#include "CEntity.h";

class CMobEffect {
public:
	virtual void Destructor();
	virtual void applyEffects(C_Entity*, int, int);
	virtual void removeEffects(C_Entity*);
	virtual void applyInstantaneousEffect(C_Entity*, C_Entity*, C_Entity*, int, float);
	virtual bool isInstantaneous(void);
	virtual int getAttributeModifierValue(int, class AttributeModifier const &);
};