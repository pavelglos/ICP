#include "SkyBox.h"

GLuint Skybox::LoadTexture(const char* filename) {
	GLuint texture;
	cv::Mat img;
	cv::Mat flipedImg;

	img = cv::imread(filename);
	
	
	if (img.empty())
	{
		std::cerr << "Texture load failed: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	if (img.channels() != 3)
	{
		std::cerr << "File is not RGB? No. channels: " << img.channels() << std::endl;
		exit(EXIT_FAILURE);
	}

	cv::flip(img, flipedImg, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, flipedImg.cols, flipedImg.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, flipedImg.data);

	return texture;
}

int Skybox::draw(const float size) {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	// Center the skybox
	x = y = z = -size / 2;
	// Bind the BACK textures of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x + size, y, z);
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x + size, y + size, z);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x, y + size, z);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x, y, z);
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x, y, z + size);
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x, y + size, z + size);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x + size, y, z + size);
	glEnd();
	
	// zem
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x + size, y, z + size); 
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x, y, z + size);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x + size, y, z);
	glEnd();
	

	// obloha
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x + size, y + size, z);
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x, y + size, z + size);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x, y + size, z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x, y + size, z);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x, y + size, z + size);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x, y, z + size);
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x, y, z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);    glVertex3f(x + size, y, z);
	glTexCoord2f(1.0f, 0.0f);    glVertex3f(x + size, y, z + size);
	glTexCoord2f(1.0f, 1.0f);    glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(0.0f, 1.0f);    glVertex3f(x + size, y + size, z);
	glEnd();
	
	return EXIT_SUCCESS;
}

int Skybox::init(void) {
	int i;

	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &i);
	std::cout << "Max texture units: " << i << std::endl;

	glActiveTexture(GL_TEXTURE0);

	this->textures[0] = LoadTexture("resources\\skybox\\back.jpg"); //load the textures
	this->textures[1] = LoadTexture("resources\\skybox\\front.jpg"); //load the textures
	this->textures[2] = LoadTexture("resources\\skybox\\left.jpg"); //load the textures
	this->textures[3] = LoadTexture("resources\\skybox\\right.jpg"); //load the textures
	this->textures[4] = LoadTexture("resources\\skybox\\up.jpg"); //load the textures
	this->textures[5] = LoadTexture("resources\\skybox\\down.jpg"); //load the textures

	return EXIT_SUCCESS;
}

int Skybox::destroy(void) {
	glDeleteTextures(6, this->textures);
	return EXIT_SUCCESS;
}
