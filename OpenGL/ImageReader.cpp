#include "ImageReader.h"
#include "STBI_Image.h"

bool ReadImage(const std::string& filepath, uint32_t& textureID)
{
	struct stat buffer;
	if (filepath == "" || stat(filepath.c_str(), &buffer) != 0) {
		return false;
	}

	int textureWidth = 1;
	int textureHeight = 1;
	int channels = 4;
	unsigned char * textureData = stbi_load(filepath.c_str(), &textureWidth, &textureHeight, &channels, 4);
	GLTest(glGenTextures(1, &textureID));
	GLTest(glBindTexture(GL_TEXTURE_2D, textureID));

	GLTest(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLTest(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLTest(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLTest(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLTest(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData));

	GLTest(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(textureData);
	return true;
}
