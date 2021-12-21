#pragma once
#include "Module.h"
class EditionFaker : public IModule {
private:
	int edition = 0;
public:
	EditionFaker();
	~EditionFaker();

	int getFakedEditon();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
