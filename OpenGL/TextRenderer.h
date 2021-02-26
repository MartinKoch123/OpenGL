#pragma once
//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  
#include "Shader.h"
#include <map>
#include "Tools.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "GLMcheckError.h"

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};


class TextRenderer {
public:
	static void write(std::string text, float x, float y, float scale, glm::vec3 color);
	static void writeLines(std::vector<std::string> strings, float x, float y, float scale, glm::vec3 color);
	static void initialize(unsigned int screenWidth, unsigned int screenHeight);
private:
	TextRenderer();
	
	static bool initialized;
	static GLuint VAO, VBO;
	static Shader* shader;
	static std::map<GLchar, Character> Characters;
	static const float lineHeight;
};

