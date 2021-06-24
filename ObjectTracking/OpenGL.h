#pragma once

#include <iostream>
// OpenGL Extension Wrangler
#include <GL/glew.h> 
#include <GL/wglew.h> //WGLEW = Windows GL Extension Wrangler (change for different platform) 

// GLFW toolkit
#include <GLFW/glfw3.h>

// OpenGL math
#include <glm/glm.hpp>

// OpenGL textures
#include <gli/gli.hpp>

#include "Globals.h"

void init_glfw(void);
void init_glew(void);
void gl_print_info(void);
static void finalize(int code);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void fbsize_callback(GLFWwindow* window, int width, int height);