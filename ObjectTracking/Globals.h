#pragma once

#include <opencv2\opencv.hpp>
#include <GLFW/glfw3.h>

struct s_globals {
	GLFWwindow* window;
	int height;
	int width;
	double app_start_time;
	cv::VideoCapture capture;
}; 

extern s_globals globals;