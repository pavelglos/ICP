#include "MovingImage.h"


cv::Point ProcessFrameGL(cv::Mat& frame)
{
	double h_low = 128.0;
	double s_low = 128.0;
	double v_low = 128.0;
	double h_hi = 255.0;
	double s_hi = 255.0;
	double v_hi = 255.0;
	cv::Point result = { 0,0 };
	int cnt = 0, sumX = 0, sumY = 0;

	// analyze the image

	cv::Mat scene_hsv, scene_threshold;

	cv::cvtColor(frame, scene_hsv, cv::COLOR_BGR2HSV);

	cv::Scalar lower_threshold = cv::Scalar(h_low, s_low, v_low);
	cv::Scalar upper_threshold = cv::Scalar(h_hi, s_hi, v_hi);
	cv::inRange(scene_hsv, lower_threshold, upper_threshold, scene_threshold);

	std::vector<cv::Point> whitePixels;
	cv::findNonZero(scene_threshold, whitePixels);
	cnt = whitePixels.size();

	for (int i = 0; i < whitePixels.size(); i++)
	{
		cv::Point point;
		point.x = whitePixels[i].x;
		point.y = whitePixels[i].y;

		sumX += point.x;
		sumY += whitePixels[i].y;

	}


	if (cnt > 0)
	{
		result.x = sumX / cnt;
		result.y = sumY / cnt;
	}
	else
	{
		result.x = 0;
		result.y = 0;
	}
	return result;
}

GLuint MatToTexture(const cv::Mat& mat) 
{
	// Generate a number for our textureID's unique handle
	GLuint textureID;
	glGenTextures(1, &textureID);

	// Bind to our texture handle
	glBindTexture(GL_TEXTURE_2D, textureID);

	// texture application method - modulation
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// texture data alignment (single byte = basic, slow, but safe option) 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// apply textures as tiles
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // tiling in S axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // tiling in T axis 

	// Create the texture
	glTexImage2D(GL_TEXTURE_2D,     // Type of texture
		0,                 // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB,            // Internal colour format to convert to
		mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
		mat.rows,          // Image height i.e. 480 for Kinect in standard mode
		0,                 // Border width in pixels (can either be 1 or 0)
		GL_BGR,				// Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE,  // Image data type
		mat.ptr());        // The actual image data itself

	//texture filters
	// bilinear - nicer & slower
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return textureID;
}

void DrawFrameGL(cv::Mat &frame)
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use ModelView matrix for following trasformations (translate,rotate,scale)
	
	glMatrixMode(GL_MODELVIEW);
	// Clear all tranformations
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	GLuint texture = MatToTexture(frame);
	// Draw something
	// glRasterPos2i(0, 0);
	// cv::flip(frame, frame, 0);

	// glDrawPixels(frame.cols, frame.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, frame.data);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(globals.width, globals.height);
	glTexCoord2i(0, 1); glVertex2i(globals.width, 0);
	glTexCoord2i(1, 1); glVertex2i(0, 0);
	glTexCoord2i(1, 0); glVertex2i(0, globals.height);
	glEnd();

	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
	// Swap front and back buffers 
	// Calls glFlush() inside
	glfwSwapBuffers(globals.window);

	// Poll for and process events
	glfwPollEvents();
}
