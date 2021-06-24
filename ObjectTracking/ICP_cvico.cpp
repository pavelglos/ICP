// ICP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>

#include <opencv2\opencv.hpp>

// OpenGL Extension Wrangler
#include <GL/glew.h> 
#include <GL/wglew.h> //WGLEW = Windows GL Extension Wrangler (change for different platform) 

// GLFW toolkit
#include <GLFW/glfw3.h>

// OpenGL math
#include <glm/glm.hpp>

// OpenGL textures
#include <gli/gli.hpp>

#include "DrawPatterns.h"
#include "MovingImage.h"
#include "Globals.h"
#include "OpenGL.h"

static void init_opengl(void);
static void init_video(void);

static cv::Mat img1, img2, img3;
static int crossSize = 35;

void ProcessFrame(std::vector<cv::Point2i>& result)
{
	// init
	cv::Point2i centerPoint;

	cv::Mat* currentImg;
	currentImg = &img1;
	std::atomic<cv::Mat*> grabImg = new cv::Mat;

	while (!glfwWindowShouldClose(globals.window))
	{
		globals.capture.read(*grabImg);
		centerPoint = ProcessFrameGL(*grabImg);
		drawCross(*grabImg, centerPoint.x, centerPoint.y, crossSize);
		result.push_back(centerPoint);

		if (currentImg == &img1)
		{
			currentImg = &img2;
			img1 = *grabImg;
		}
		if (currentImg == &img2)
		{
			currentImg = &img3;
			img2 = *grabImg;
		}
		if (currentImg == &img3)
		{
			currentImg = &img1;
			img3 = *grabImg;
		}
	}
	
}

int main(int argc, char* argv[])
{
	std::thread thread;
	std::vector<cv::Point2i> result{};
	std::atomic<cv::Mat*> drawImg;
	
	init_video();
	init_opengl();
	
	drawImg = &img1;

	thread = std::thread(ProcessFrame, std::ref(result));

	auto start = std::chrono::system_clock::now();
	int frames_processed = 0;

	while (!glfwWindowShouldClose(globals.window))
	{		
		DrawFrameGL(std::ref(*drawImg));
		frames_processed++;
		// switch :)
		if (drawImg == &img1)
		{
			drawImg = &img2;
		}
		else if (drawImg == &img2)
		{
			drawImg = &img3;
		}
		else if (drawImg == &img3)
		{
			drawImg = &img1;
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "sec" << std::endl;
	std::cout << "fps: " << frames_processed / elapsed_seconds.count() << std::endl;
	thread.join();
}

static void init_video(void)
{
	// globals.capture = cv::VideoCapture("video.mkv");
	globals.capture = cv::VideoCapture(0);

	if (!globals.capture.isOpened())
	{
		std::cerr << "no camera" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Camera " <<
			": width=" << globals.capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
			", height=" << globals.capture.get(cv::CAP_PROP_FRAME_HEIGHT) <<
			std::endl;
	}
}

//OpenGL
static void init_opengl(void)
{
	init_glfw();
	init_glew();
	gl_print_info();
}

