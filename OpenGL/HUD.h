#pragma once
#include "TextRenderer.h"
#include "FramerateCalculator.h"
#include <glm\glm.hpp>
#include <vector>
#include "Mat.h"

class HUDelement {
public:
	HUDelement() {};
	HUDelement(float xPercentage, float yPercentage, float scale, Vec3 color, unsigned int numberLines);
	std::vector<std::string> lines;
	float xPercentage;
	float yPercentage;
	float scale;
	Vec3 color;
};


class HUD {
public:
	HUD() {};
	HUD(unsigned int screenWidth, unsigned int screenHeight);
	void draw();
	void addElement(HUDelement* element);
private:	
	std::vector<HUDelement*> elements;
	unsigned int screenWidth, screenHeight;
};



