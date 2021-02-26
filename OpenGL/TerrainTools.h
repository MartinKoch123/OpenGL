#pragma once
#include "Terrain.h"
#include "Tools.h"
#include <cmath>
#include "Mat.h"

namespace TerrainTools {

	void generateSinNoise(HeightMapSuper *heightMap);

	void addPerlinNoise(HeightMapSuper * heightMap, unsigned int numberCells, float amplitude);

	void smoothHeightMap(HeightMapSuper *heightMap, int smoothSize);

	float sin2D(unsigned int x, unsigned int z, float frequency, float phaseShift);

}