#include "HUD.h"

HUD::HUD(unsigned int screenWidth, unsigned int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	elements = std::vector<HUDelement*>();
}

void HUD::draw() {
	for (unsigned int i = 0; i < elements.size(); i++) {
		if (elements[i] == NULL)
			continue;
		TextRenderer::writeLines(elements[i]->lines, elements[i]->xPercentage * screenWidth, (1.0f - elements[i]->yPercentage) * screenHeight, elements[i]->scale, elements[i]->color.toGLM());
	}
}

void HUD::addElement(HUDelement * element) {
	if (element != NULL)
		elements.push_back(element);
}

HUDelement::HUDelement(float xPercentage, float yPercentage, float scale, Vec3 color, unsigned int numberLines) :
	xPercentage(xPercentage), yPercentage(yPercentage), scale(scale), color(color) {
	for (unsigned int i = 0; i < numberLines; i++){
		lines.push_back("");
	}
}
