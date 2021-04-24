#pragma once
#include "Mat.h"

class HeightMap {
public:
	HeightMap(unsigned int size);
	~HeightMap() { delete data; };
	float get(unsigned int x, unsigned int z) { return data[x + z * _size]; };
	void set(unsigned int x, unsigned int z, float value) { data[x + z * _size] = value; };
	void add(unsigned int x, unsigned int z, float value) { data[x + z * _size] += value; };
	unsigned int size() { return _size; };
private:
	float* data;
	unsigned int _size;
};

class Terrain {
public:
	Terrain(float width, HeightMap*heightMap);
	float height(float x, float z);
	float width() { return _width; }
	HeightMap* heightMap() { return _heightMap; }
private:
	HeightMap* _heightMap;
	float _width;
	float _edgeLength{0.0f};
};
