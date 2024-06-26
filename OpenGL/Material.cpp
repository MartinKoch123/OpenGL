#include "Material.h"


const float Material::MATERIAL_DATA[] = {
	0.1f, 0.1f, 0.1f, 0.7f, 0.7f, 0.7f, 0.4f, 0.4f, 0.4f, 0.0f, //default			
	0.0215f, 0.1745f, 0.0215f, 0.07568f, 0.61424f, 0.07568f, 0.633f, 0.727811f, 0.633f, 0.6f, //emerald			
	0.135f, 0.2225f, 0.1575f, 0.54f, 0.89f, 0.63f, 0.316228f, 0.316228f, 0.316228f, 0.1f, //jade			
	0.05375f, 0.05f, 0.06625f, 0.18275f, 0.17f, 0.22525f, 0.332741f, 0.328634f, 0.346435f, 0.3f, //obsidian		
	0.25f, 0.20725f, 0.20725f, 1.0f, 0.829f, 0.829f, 0.296648f, 0.296648f, 0.296648f, 0.088f, //pearl			
	0.1745f, 0.01175f, 0.01175f, 0.61424f, 0.04136f, 0.04136f, 0.727811f, 0.626959f, 0.626959f, 0.6f, //ruby			
	0.1f, 0.18725f, 0.1745f, 0.396f, 0.74151f, 0.69102f, 0.297254f, 0.30829f, 0.306678f, 0.1f, //turquoise		
	0.329412f, 0.223529f, 0.027451f, 0.780392f, 0.568627f, 0.113725f, 0.992157f, 0.941176f, 0.807843f, 0.21794872f, //brass			
	0.2125f, 0.1275f, 0.054f, 0.714f, 0.4284f, 0.18144f, 0.393548f, 0.271906f, 0.166721f, 0.2f, //bronze			
	0.25f, 0.25f, 0.25f, 0.4f, 0.4f, 0.4f, 0.774597f, 0.774597f, 0.774597f, 0.6f, //chrome			
	0.19125f, 0.0735f, 0.0225f, 0.7038f, 0.27048f, 0.0828f, 0.256777f, 0.137622f, 0.086014f, 0.1f, //copper			
	0.24725f, 0.1995f, 0.0745f, 0.75164f, 0.60648f, 0.22648f, 0.628281f, 0.555802f, 0.366065f, 0.4f, //gold			
	0.19225f, 0.19225f, 0.19225f, 0.50754f, 0.50754f, 0.50754f, 0.508273f, 0.508273f, 0.508273f, 0.4f, //silver			
	0.0f, 0.0f, 0.0f, 0.01f, 0.01f, 0.01f, 0.50f, 0.50f, 0.50f, 0.25f, // black plastic	
	0.0f, 0.1f, 0.06f, 0.0f, 0.50980392f, 0.50980392f, 0.50196078f, 0.50196078f, 0.50196078f, 0.25f, // cyan plastic	
	0.0f, 0.0f, 0.0f, 0.1f, 0.35f, 0.1f, 0.45f, 0.55f, 0.45f, 0.25f, // green plastic	
	0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.7f, 0.6f, 0.6f, 0.25f, //red plastic		
	0.0f, 0.0f, 0.0f, 0.55f, 0.55f, 0.55f, 0.70f, 0.70f, 0.70f, 0.25f, // white plastic	
	0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.60f, 0.60f, 0.50f, 0.25f, //yellow plastic	
	0.02f, 0.02f, 0.02f, 0.01f, 0.01f, 0.01f, 0.4f, 0.4f, 0.4f, 0.078125f, // black rubber	
	0.0f, 0.05f, 0.05f, 0.4f, 0.5f, 0.5f, 0.04f, 0.7f, 0.7f, 0.078125f, // cyan rubber		
	0.0f, 0.05f, 0.0f, 0.4f, 0.5f, 0.4f, 0.04f, 0.7f, 0.04f, 0.078125f, // green rubber	
	0.05f, 0.0f, 0.0f, 0.5f, 0.4f, 0.4f, 0.7f, 0.04f, 0.04f, 0.078125f, // red rubber		
	0.05f, 0.05f, 0.05f, 0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f, 0.078125f, // white rubber	
	0.05f, 0.05f, 0.0f, 0.5f, 0.5f, 0.4f, 0.7f, 0.7f, 0.04f, 0.078125f, // yellow rubber	

	0.30f, 0.74f, 0.21f, 0.30f, 0.74f, 0.21f, 0.0f, 0.0f, 0.0f, 0.1f, // grass	
	0.2f, 0.31f, 0.10f, 0.39f, 0.62f, 0.20f, 0.0f, 0.0f, 0.0f, 0.1f, // dark grass	
	0.05f, 0.10f, 0.01f, 0.09f, 0.20f, 0.02f, 0.0f, 0.0f, 0.0f, 0.1f // pine tree
};

Material::Material(MaterialType type) {
	int m = (int)type * 10;
	ambient = glm::vec3(MATERIAL_DATA[m], MATERIAL_DATA[m + 1], MATERIAL_DATA[m + 2]);
	diffuse = glm::vec3(MATERIAL_DATA[m + 3], MATERIAL_DATA[m + 4], MATERIAL_DATA[m + 5]);
	specular = glm::vec3(MATERIAL_DATA[m + 6], MATERIAL_DATA[m + 7], MATERIAL_DATA[m + 8]);
	shininess = MATERIAL_DATA[m + 9];
}

bool Material::operator==(const Material &other) const {
	return ambient == other.ambient && diffuse == other.diffuse && specular == other.specular && shininess == other.shininess;
}

bool Material::operator!=(const Material &other) const {
	return !(*this == other);
}
