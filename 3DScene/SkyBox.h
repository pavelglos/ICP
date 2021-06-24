#ifndef __skybox_h__
#define __skybox_h__
#include <GL/glew.h>
#include <iostream>
#include <opencv2\opencv.hpp>

class Skybox {
private:
	GLuint textures[6]; //the array for our textures

	GLuint LoadTexture(const char* filename);
public:
	int init(void);
	int draw(const float size);
	int destroy(void);
};

#endif __skybox_h__
