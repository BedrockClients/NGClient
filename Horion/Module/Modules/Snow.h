#pragma once
#include <sstream>
#include "../../DrawUtils.h"
#include "Module.h"
#include "../../../Utils/Json.hpp"
#include <optional>

class SnowParticle {
public:
	vec2_t screenPosition;
	MC_Color colour;
	std::string text;
	SnowParticle(vec2_t screenPosition, MC_Color colour, std::string text) {
		this->screenPosition = screenPosition;
		this->colour = colour;
		this->text = text;
	}
};

class Snow : public IModule {
public:
	Snow() : IModule(0, Category::VISUAL, "Cool Visuals") {}
	~Snow(){};
	std::vector<SnowParticle> snowParticles;
	std::vector<MC_Color> SnowMC_Colors = std::vector<MC_Color>{MC_Color(254, 254, 254), MC_Color(255, 255, 255), MC_Color(253, 253, 253)};
	int SnowTick = 0;

	float randFloatYes4206969(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	virtual const char* getModuleName() override { return ("Snow"); }

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) {

			float width = g_Data.getGuiData()->windowSize.x;
			float height = g_Data.getGuiData()->windowSize.y;

			if (SnowTick == 40) {
				SnowParticle particle = SnowParticle(vec2_t(randFloatYes4206969(0, width - 10), -12.5f), SnowMC_Colors.at((int)randFloatYes4206969(0, 2)), std::string("*"));
				snowParticles.push_back(particle);
				SnowTick = 0;
			} else
				SnowTick++;

			for (int i = 0; i < snowParticles.size(); i++) {
				SnowParticle* particle = &snowParticles.at(i);
				DrawUtils::drawText(particle->screenPosition, &particle->text, particle->colour, 2.5f, 1.0f);
				particle->screenPosition.y = particle->screenPosition.y + 1.f;

				if (particle->screenPosition.y >= height)
					snowParticles.erase(snowParticles.begin() + i);
			}

			DrawUtils::flush();
		}
};