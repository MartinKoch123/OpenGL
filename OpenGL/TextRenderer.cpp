#include "TextRenderer.h"


bool TextRenderer::initialized = false;
GLuint TextRenderer::VAO = 0;
GLuint TextRenderer::VBO = 0;
Shader* TextRenderer::shader = NULL;
std::map<GLchar, Character> TextRenderer::Characters;
const float TextRenderer::lineHeight = 45.0f;

TextRenderer::TextRenderer() {}


void TextRenderer::write(std::string text, float x, float y, float scale, glm::vec3 color) {
	if (!initialized) {
		std::cout << "TextRenderer has not been initialized." << std::endl;
		return;
	}

	// Activate corresponding render state	
	shader->use();
	glUniform3f(glGetUniformLocation(shader->ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::initialize(unsigned int screenWidth, unsigned int screenHeight) {

	glm::mat4 projectionFont = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);

	shader = new Shader(FILE_FONT_VERTEX_SHADER.c_str(), FILE_FONT_FRAGMENT_SHADER.c_str());
	glCheckError();
	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionFont));
	glCheckError();


	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	FT_Face face;
	if (FT_New_Face(ft, "res/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++) {
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCheckError();
	glGenVertexArrays(1, &VAO);
	glCheckError();
	glGenBuffers(1, &VBO);
	glCheckError();
	glBindVertexArray(VAO);
	glCheckError();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glCheckError();
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glCheckError();
	glEnableVertexAttribArray(0);
	glCheckError();
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glCheckError();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glCheckError();
	glBindVertexArray(0);
	glCheckError();
	initialized = true;
}

void TextRenderer::writeLines(std::vector<std::string> strings, float x, float y, float scale, glm::vec3 color) {
	for (unsigned int i = 0; i < strings.size(); i++) {
		write(strings[i], x, y - (float)i*lineHeight*scale, scale, color);
	}
}