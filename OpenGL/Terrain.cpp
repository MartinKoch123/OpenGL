#include "Terrain.h"

Terrain::Terrain(float width, HeightMapSuper *heightMap) : width(width){
	if (width < 0.0f)
		this->width = 10;
	this->heightMap = heightMap;
	if (heightMap == NULL)
		edgeLength = 0.0f;
	else
		edgeLength = width / (heightMap->getSize() - 1);
}

float Terrain::getHeight(float x, float z) {
	if (abs(x) >= width / 2 || abs(z) >= width / 2)
		return 0.0f;
	x += width / 2;
	z += width / 2;
	int iX = (int)(x / edgeLength);
	int iZ = (int)(z / edgeLength);
	float xRatio = (x - iX*edgeLength)/edgeLength;
	float zRatio = (z - iZ*edgeLength)/edgeLength;

	float result = heightMap->get(iX, iZ);
	if (xRatio > zRatio) {
		result += xRatio * (heightMap->get(iX + 1, iZ) - heightMap->get(iX, iZ));
		result += zRatio * (heightMap->get(iX + 1, iZ + 1) - heightMap->get(iX + 1, iZ));
	}
	else {
		result += zRatio * (heightMap->get(iX, iZ + 1) - heightMap->get(iX, iZ));
		result += xRatio * (heightMap->get(iX + 1, iZ + 1) - heightMap->get(iX, iZ + 1));
	}

	return result;
}




