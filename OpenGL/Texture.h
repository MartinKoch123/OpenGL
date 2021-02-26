#pragma once
class Texture
{
public:
	Texture(char* filePath);
	Texture();
	~Texture();
	void use();
	void use(unsigned int ID);
private:
	unsigned int ID;
};

