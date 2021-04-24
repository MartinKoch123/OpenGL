#include "Terrain.h"

HeightMap::HeightMap(unsigned int size) : _size(size) {
	data = new float[size * size];
	for (int i = 0; i < size * size; i++)
		data[i] = 0;
};

Terrain::Terrain(float width, HeightMap*heightMap) : _width(width), _heightMap(heightMap){
	if (width < 0.0f)
		throw std::invalid_argument("Width must be non-negative.");
	if (heightMap == nullptr)
		throw std::invalid_argument("Height map must not be null.");
	_edgeLength = width / (_heightMap->size() - 1);
}

float Terrain::height(float x, float z) {
	if (abs(x) >= _width / 2 || abs(z) >= _width / 2)
		return 0.0f;
	x += _width / 2;
	z += _width / 2;
	int iX = (int)(x / _edgeLength);
	int iZ = (int)(z / _edgeLength);
	float xRatio = (x - iX*_edgeLength)/_edgeLength;
	float zRatio = (z - iZ*_edgeLength)/_edgeLength;
	float result = _heightMap->get(iX, iZ);
	if (xRatio > zRatio) {
		result += xRatio * (_heightMap->get(iX + 1, iZ) - _heightMap->get(iX, iZ));
		result += zRatio * (_heightMap->get(iX + 1, iZ + 1) - _heightMap->get(iX + 1, iZ));
	}
	else {
		result += zRatio * (_heightMap->get(iX, iZ + 1) - _heightMap->get(iX, iZ));
		result += xRatio * (_heightMap->get(iX + 1, iZ + 1) - _heightMap->get(iX, iZ + 1));
	}
	return result;
}

