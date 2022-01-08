#pragma once
#include <vcruntime_string.h>

#include "TextHolder.h"

class Attribute {
public:
	__int64 hash;
	__int64 hashedStringHash;
	class TextHolder attributeName;

private:
	char __padding[0x32];

public:
	Attribute() {
		memset(this, 0x0, sizeof(Attribute));
	}

	Attribute(__int64 hash) {
		memset(this, 0x0, sizeof(Attribute));
		this->hash = hash;
	}
};

class HealthAttribute : public Attribute {
public:
	HealthAttribute() { this->hash = 25769804032; }
};

class PlayerHungerAttribute : public Attribute {
public:
	PlayerHungerAttribute() { this->hash = 4294967552; }
};

class MovementAttribute : public Attribute {
public:
	MovementAttribute() { this->hash = 38654705921; }
};

class AbsorptionAttribute : public Attribute {
public:
	AbsorptionAttribute() { this->hash = 55834575105; }
};

class PlayerSaturationAttribute : public Attribute {
public:
	PlayerSaturationAttribute() { this->hash = 8589934848; }
};

class AttributeInstance {
private:
	char __padding[0x74];

public:
	float minimumValue;
	float maximumValue;
	float currentValue;

	~AttributeInstance();
	virtual void tick(void);
};

//Full credit to Disepi for this lol