#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>


Texture::Texture(char* filePath) {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;

	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture." << std::endl;
	}
	stbi_image_free(data);
}

Texture::Texture() {

}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::use(unsigned int textureUnit) {
	if (textureUnit == 0)
		glActiveTexture(GL_TEXTURE0);
	if (textureUnit == 1)
		glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ID);
}


Texture::~Texture() {
}
