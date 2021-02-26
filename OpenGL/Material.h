#pragma once
#include <glm\glm.hpp>

struct Material {
	enum MaterialType {
		default, emerald, jade, obsidian, pearl, ruby, turquoise, brass, bronze, chrome, copper,
		gold, silver, black_plastic, cyan_plastic, green_plastic, red_plastic, white_plastic,
		yellow_plastic, black_rubber, cyan_rubber, green_rubber, red_rubber, white_rubber, yellow_rubber,
		grass, dark_grass, pine_tree
	};
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}
	Material(MaterialType type);
	Material() {};
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	bool Material::operator==(const Material &other) const;
	bool Material::operator!=(const Material &other) const;
	
private:
	static const float MATERIAL_DATA[];

};

