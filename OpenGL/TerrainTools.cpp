#include "TerrainTools.h"


void TerrainTools::smoothHeightMap(HeightMapSuper *heightMap, int smoothSize) {
	float sum, divisor, weight;

	for (unsigned int iX = smoothSize; iX < heightMap->getSize() - smoothSize; iX++) {
		for (unsigned int iZ = smoothSize; iZ < heightMap->getSize() - smoothSize; iZ++) {

			sum = 0.0f;
			divisor = 0.0f;
			for (int xOff = -smoothSize; xOff <= smoothSize; xOff++) {
				for (int zOff = -smoothSize; zOff <= smoothSize; zOff++) {
					if (xOff == 0 && zOff == 0)
						continue;
					weight = 1.0f / sqrt((float)(xOff*xOff) + (float)(zOff*zOff));
					sum += weight * heightMap->get(iX + xOff, iZ + zOff);
					divisor += weight;
				}
			}
			heightMap->set(iX, iZ, sum / divisor);
		}
	}
}

void TerrainTools::generateSinNoise(HeightMapSuper *heightMap) {

	float height;

	std::vector<Vec2> sinNoises;
	sinNoises.push_back(Vec2(12.0f, 1.0f / 100.0f));
	sinNoises.push_back(Vec2(5.0f, 1.0f / 50.0f));
	sinNoises.push_back(Vec2(5.0f, 1.0f / 45.0f));
	sinNoises.push_back(Vec2(5.0f, 1.0f / 40.0f));
	sinNoises.push_back(Vec2(1.0f, 1.0f / 25.0f));
	sinNoises.push_back(Vec2(1.0f, 1.0f / 20.0f));
	sinNoises.push_back(Vec2(1.0f, 1.0f / 15.0f));

	for (unsigned int iX = 0; iX < heightMap->getSize(); iX++) {
		for (unsigned int iZ = 0; iZ < heightMap->getSize(); iZ++) {
			height = 0.0f;
			for (unsigned int iN = 0; iN < sinNoises.size(); iN++) {
				height += sinNoises[iN].x() * sin2D(iX, iZ, sinNoises[iN].y(), 0.0f);
			}

			heightMap->set(iX, iZ, height);
		}
	}
}

void TerrainTools::addPerlinNoise(HeightMapSuper * heightMap, unsigned int numberCells, float amplitude) {

	std::vector<std::vector<Vec2>> gradients;
	Vec2 gradient;
	for (unsigned int iX = 0; iX <= numberCells; iX++) {
		gradients.push_back(std::vector<Vec2>());
		for (unsigned int iZ = 0; iZ <= numberCells; iZ++) {
			gradient = Vec2(randomFloatNonZero11(), randomFloatNonZero11());
			gradients[iX].push_back(gradient.normalize());
		}
	}

	float xMap, zMap, dotGradPosx0z0, dotGradPosx1z0, dotGradPosx0z1, dotGradPosx1z1, noiseValue, av0, av1, xMod, yMod;
	int xCellIndex, zCellIndex;
	Vec2 fromCornerx0z0, fromCornerx1z0, fromCornerx0z1, fromCornerx1z1;
	for (unsigned int iX = 0; iX < heightMap->getSize(); iX++) {
		xMap = (float)iX / (float)(heightMap->getSize() - 1);
		for (unsigned int iZ = 0; iZ < heightMap->getSize(); iZ++) {
			zMap = (float)iZ / (float)(heightMap->getSize() - 1);

			xCellIndex = (int)floor(xMap * numberCells);
			zCellIndex = (int)floor(zMap * numberCells);
			fromCornerx0z0 = Vec2(xMap * numberCells - xCellIndex, zMap * numberCells - zCellIndex);
			fromCornerx1z0 = Vec2(-1 + fromCornerx0z0.x(), fromCornerx0z0.y());
			fromCornerx0z1 = Vec2(fromCornerx0z0.x(), -1 + fromCornerx0z0.y());
			fromCornerx1z1 = Vec2(-1 + fromCornerx0z0.x(), -1 + fromCornerx0z0.y());

			dotGradPosx0z0 = scalar(fromCornerx0z0, gradients[xCellIndex][zCellIndex]);
			if (xMap < 1.0f) {
				dotGradPosx1z0 = scalar(fromCornerx1z0, gradients[xCellIndex + 1][zCellIndex]);
			}
			if (zMap < 1.0f) {
				dotGradPosx0z1 = scalar(fromCornerx0z1, gradients[xCellIndex][zCellIndex + 1]);
			}
			if (xMap < 1.0f && zMap < 1.0f) {
				dotGradPosx1z1 = scalar(fromCornerx1z1, gradients[xCellIndex + 1][zCellIndex + 1]);
			}
			
			xMod = 6 * pow(fromCornerx0z0.x(), 5) - 15 * pow(fromCornerx0z0.x(), 4) + 10 * pow(fromCornerx0z0.x(), 3);
			yMod = 6 * pow(fromCornerx0z0.y(), 5) - 15 * pow(fromCornerx0z0.y(), 4) + 10 * pow(fromCornerx0z0.y(), 3);
			
			av0 = dotGradPosx0z0 * (1.0f - xMod) + dotGradPosx1z0 * xMod;
			av1 = dotGradPosx0z1 * (1.0f - xMod) + dotGradPosx1z1 * xMod;

			noiseValue = amplitude * (av0 * (1.0f - yMod) + av1 * yMod);


			heightMap->add(iX, iZ, noiseValue);
		}
	}

}

float TerrainTools::sin2D(unsigned int x, unsigned int z, float frequency, float phaseShift) {
	return sin((float)x*2.0f*PI*frequency + phaseShift) + sin((float)z * 2.0f * PI*frequency + phaseShift);
}
