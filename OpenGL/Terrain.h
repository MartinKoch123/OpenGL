#pragma once
#include "Mat.h"



class HeightMapSuper {
public:
	virtual float get(unsigned int x, unsigned int z) = 0;
	virtual void set(unsigned int x, unsigned int y, float value) = 0;
	virtual void add(unsigned int x, unsigned int y, float value) = 0;
	virtual unsigned int getSize() = 0;
};

template <unsigned int size>
class HeightMap : public HeightMapSuper {
public:
	HeightMap();
	float get(unsigned int x, unsigned int z);
	void set(unsigned int x, unsigned int z, float value);
	void add(unsigned int x, unsigned int z, float value);
	unsigned int getSize();
private:
	float data[size][size];
};


class Terrain {
public:
	Terrain(float width, HeightMapSuper *heightMap);
	Terrain() : Terrain(1, NULL) {};
	HeightMapSuper *heightMap;
	float getHeight(float x, float z);
	float width;
private:
	float edgeLength;
};

template<unsigned int size>
inline HeightMap<size>::HeightMap() {
	for (unsigned int x = 0; x < size; x++) {
		for (unsigned int z = 0; z < size; z++) {
			data[x][z] = 0.0f;
		}
	}
}

template<unsigned int size>
inline float HeightMap<size>::get(unsigned int x, unsigned int z) {
	if (x >= size || z >= size)
		return 0.0f;
	return data[x][z];
}

template<unsigned int size>
inline void HeightMap<size>::set(unsigned int x, unsigned int z, float value) {
	if (x >= size || z >= size)
		return;
	data[x][z] = value;
}

template<unsigned int size>
inline void HeightMap<size>::add(unsigned int x, unsigned int z, float value) {
	set(x, z, value + get(x, z));
}

template<unsigned int size>
inline unsigned int HeightMap<size>::getSize() {
	return size;
}
