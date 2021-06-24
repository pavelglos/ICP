#pragma once

#include <iostream>
#include <opencv2\opencv.hpp>
#include <chrono>
#include <GL/glew.h>

#include "DrawPatterns.h"
#include "Globals.h"

cv::Point ProcessFrameGL(cv::Mat& frame);
GLuint MatToTexture(const cv::Mat& mat);
void DrawFrameGL(cv::Mat& frame);