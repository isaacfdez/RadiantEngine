#include "ModuleTextures.h"
#include <GL\glew.h>
#include <il.h>

bool ModuleTextures::Init() {
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	return true;
}

unsigned int ModuleTextures::LoadTexture(const char* path) {
	unsigned int image, texture_id;

	ilGenImages(1, &image);
	ilBindImage(image);

	bool success = ilLoadImage(path);

	if (success) {
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		if (!success) {
			return false;
		}

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			ilGetInteger(IL_IMAGE_BPP),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			GL_UNSIGNED_BYTE,
			ilGetData()
		);
	}
	else {
		return false;
	}
	ilDeleteImages(1, &image);

	return texture_id;
}

bool ModuleTextures::CleanUp() {
	return true;
}

