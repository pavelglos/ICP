#pragma once

#include <opencv2\opencv.hpp>
#include <GLFW/glfw3.h>
// #include "mesh.h"

struct s_globals {
	GLFWwindow* window;
	int height;
	int width;
	double app_start_time;
}; 

extern s_globals globals;

typedef struct s_Avatar {
	float posX;
	float posY; // height
	float posZ;
	float yaw;
	float pitch;
	float roll;
	float movementSpeed;
};

extern s_Avatar Avatar;

void avatarMoveForward();
void avatarMoveBackward();
void avatarMoveLeft();
void avatarMoveRight();
void avatarMoveUp();
void avatarMoveDown();