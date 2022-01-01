#pragma once
#include "Module.h"

class NoHurtcam : public IModule{
public:
	NoHurtcam() : IModule(0, Category::VISUAL, "Disables rotation of the camera when hit") {}
	~NoHurtcam(){};
	const char* getModuleName() override { return "NoHurtcam"; }
};