// ICP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <stack>

#include <opencv2\opencv.hpp>

// OpenGL Extension Wrangler
#include <GL/glew.h> 
#include <GL/wglew.h> //WGLEW = Windows GL Extension Wrangler (change for different platform) 

// GLFW toolkit
#include <GLFW/glfw3.h>

// OpenGL math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// OpenGL textures
#include <gli/gli.hpp>

#include "Globals.h"
#include "OpenGL.h"
#include "glerror.h"

#include "mesh.h"
#include "mesh_init.h"
#include "SkyBox.h"
#include "texture.h"


static void init_opengl(void);
// static void init_video(void);

static cv::Mat img1, img2, img3 = cv::Mat();

std::stack<glm::mat4> stack_mv;

//mesh
mesh mesh_circle;
int circle_segments = 1'000'000;
mesh height_map;

// texture
// image used as a texture
cv::Mat image;

GLuint woodenBox, minecraftTex;

// skybox
Skybox skybox;

GLfloat color_red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat color_green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat color_blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat color_white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat color_grey[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat color_black[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat color_lightGreen[] = { 0.5, 1.0, 0.5, 1.0 };

GLfloat color_RedA[] = { 1.0, 0.0, 0.0, 0.3 };
GLfloat color_GreenA[] = { 0.0, 1.0, 0.0, 0.3 };
GLfloat color_BlueA[] = { 0.0, 0.0, 1.0, 0.3 };
GLfloat color_WhiteA[] = { 1.0, 1.0, 1.0, 0.3 };

// rockbox y position
float rockBoxY = 2000.0f;
bool addingRockBoxY = true;

// icebox rotation
float angleIceBox = 180.0f;

void DrawScene(glm::mat4& mv_mat4)
{
	//skybox
	
	{
		stack_mv.push(mv_mat4);
		mv_mat4 = glm::translate(mv_mat4, glm::vec3(Avatar.posX, Avatar.posY, Avatar.posZ));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_white);

		glEnable(GL_TEXTURE_2D);
		skybox.draw(20000.0);
		glDisable(GL_TEXTURE_2D);
		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();
	}
	

	//cube
	/*
	{
		stack_mv.push(mv_mat4);

		mv_mat4 = glm::translate(mv_mat4, glm::vec3(0.0f, 2000.0f, 0.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(1000.0f, 1000.0f, 1000.0f));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_Blue);
		mesh_draw_arrays(mesh_cube);

		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();

	}
	*/
	

	
	//circle
	{
		stack_mv.push(mv_mat4);

		mv_mat4 = glm::translate(mv_mat4, glm::vec3(0.0f, 2000.0f, 0.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(1000.0f, 1000.0f, 1000.0f));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_blue);
		mesh_draw_arrays(mesh_circle);

		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();

	}

	// rock box with texture

	{
		stack_mv.push(mv_mat4);
		
		if (rockBoxY > 3000.0)
		{
			addingRockBoxY = false;
		}

		if (rockBoxY < 1000.0)
		{
			addingRockBoxY = true;
		}

		if (addingRockBoxY)
		{
			rockBoxY++;
		}
		else {
			rockBoxY--;
		}
		
		mv_mat4 = glm::translate(mv_mat4, glm::vec3(-2000.0f, rockBoxY, 0.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(10.0f, 10.0f, 10.0f));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_white);

		int size = 62;
		float x, y, z;
		x = y = z = -size / 2;


		// glBindTexture(GL_TEXTURE_2D, texture_id);
		glEnable(GL_TEXTURE_2D);

		// front face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		/* 
		// posledni kosticka lavy
		glTexCoord2f(0.9375f, 0.9375f);    glVertex3f(x + size, y, z);
		glTexCoord2f(1.0f, 0.9375f);    glVertex3f(x + size, y + size, z);
		glTexCoord2f(1.0f, 1.0f);    glVertex3f(x, y + size, z);
		glTexCoord2f(0.9375f, 1.0f);    glVertex3f(x, y, z);
		*/

		// kosticka kamene
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x + size, y, z);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x + size, y + size, z);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x, y + size, z);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x, y, z);

		glEnd();
		
		// back face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x + size, y, z - size);
		glEnd();
		
		// bottom face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x, y, z);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x + size, y, z - size);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x + size, y, z);
		glEnd();
		
		// top face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x + size, y + size, z);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x, y + size, z);
		glEnd();

		// left face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x, y + size, z);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x, y, z);
		glEnd();

		// right face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0625f, 0.0f);    glVertex3f(x + size, y, z);
		glTexCoord2f(0.125f, 0.0f);    glVertex3f(x + size, y, z - size);
		glTexCoord2f(0.125f, 0.0625f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.0625f, 0.0625f);    glVertex3f(x + size, y + size, z);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();
	}

	// ice box with texture
	
	{
		stack_mv.push(mv_mat4);
		angleIceBox += 0.01;
		
		mv_mat4 = glm::translate(mv_mat4, glm::vec3(2000.0f, 2000.0f, 0.0f));
		// rotace
		mv_mat4 = glm::rotate(mv_mat4, angleIceBox, glm::vec3(0.0f, 0.0f, 1.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(10.0f, 10.0f, 10.0f));
		
		glLoadMatrixf(glm::value_ptr(mv_mat4));

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_WhiteA);

		// glBindTexture(GL_TEXTURE_2D, texture_id);
		glEnable(GL_TEXTURE_2D);

		//semi-transparent object, colour through Phong model
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		int size = 62;
		float x, y, z;
		x = y = z = -size / 2;


		
		// front face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);

		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x + size, y, z);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x + size, y + size, z);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x, y + size, z);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x, y, z);

		glEnd();
		
		// back face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x + size, y, z - size);
		glEnd();
		
		// bottom face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x, y, z);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x + size, y, z - size);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x + size, y, z);
		glEnd();
		
		// top face - wrong coord
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x + size, y + size, z);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x, y + size, z);
		glEnd();

		// left face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x, y + size, z);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x, y + size, z - size);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x, y, z - size);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x, y, z);
		glEnd();

		// right face
		glBindTexture(GL_TEXTURE_2D, minecraftTex);
		glBegin(GL_QUADS);
		glTexCoord2f(0.8125f, 0.75f);    glVertex3f(x + size, y, z);
		glTexCoord2f(0.875f, 0.75f);    glVertex3f(x + size, y, z - size);
		glTexCoord2f(0.875f, 0.8125f);    glVertex3f(x + size, y + size, z - size);
		glTexCoord2f(0.8125f, 0.8125f);    glVertex3f(x + size, y + size, z);
		glEnd();
		
		
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		
		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();
	}
	

	// quad with texture
	{
		stack_mv.push(mv_mat4);

		mv_mat4 = glm::translate(mv_mat4, glm::vec3(0.0f, 2000.0f, 0.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(5.0f, 5.0f, 5.0f));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_white);


		// glBindTexture(GL_TEXTURE_2D, texture_id);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, woodenBox);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3i(-125, -125, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3i(125, -125, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3i(125, 125, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3i(-125, 125, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();
	}
	

	//terrain
	{
		glEnable(GL_COLOR_MATERIAL);
		// Scale Value For The Terrain - size of terrain is from raster = 1024x1024
		// scale (or move further from camera...)
		float scaleValue = 3.0f;
		float terrainSize = 1024.0f;

		//save current ModelView
		stack_mv.push(mv_mat4);

		mv_mat4 = glm::translate(mv_mat4, glm::vec3(-terrainSize / 2.0f, 0.0f, -terrainSize / 2.0f));
		mv_mat4 = glm::scale(mv_mat4, glm::vec3(scaleValue, scaleValue, scaleValue));
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		// glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_blue);
		mesh_draw(height_map);

		//restore ModelView
		mv_mat4 = stack_mv.top();
		glLoadMatrixf(glm::value_ptr(mv_mat4));
		stack_mv.pop();
		glDisable(GL_COLOR_MATERIAL);
	}
	
}

static void app_loop(void)
{
	// Time measurement, FPS count etc.
	static double time_fps_old = 0.0;
	static double time_frame_old = 0.0;
	static int frame_cnt = 0;
	double time_current, time_frame_delta;


	// Run until exit is requested.
	while (!glfwWindowShouldClose(globals.window))
	{
		time_current = glfwGetTime();
		time_frame_delta = time_current - time_frame_old;
		time_frame_old = time_current;

		//FPS
		if (time_current - time_fps_old > 1.0)
		{
			time_fps_old = time_current;
			std::cout << "FPS: " << frame_cnt << std::endl;
			frame_cnt = 0;
		}
		frame_cnt++;
		// Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use ModelView matrix for following trasformations (translate,rotate,scale)
		glMatrixMode(GL_MODELVIEW);
		// Clear all tranformations
		

		// Set the camera (eye, center, up)
		{
			glm::mat4 mv_mat4;

			mv_mat4 = glm::lookAt(
				glm::vec3(Avatar.posX, Avatar.posY, Avatar.posZ),
				glm::vec3(
					Avatar.posX + (cos(glm::radians(Avatar.yaw)) * cos(glm::radians(Avatar.pitch))),
					Avatar.posY + sin(glm::radians(Avatar.pitch)),
					Avatar.posZ + (sin(glm::radians(Avatar.yaw)) * cos(glm::radians(Avatar.pitch)))
				),
				glm::vec3(0.0f, 1.0f, 0.0f));
			glLoadMatrixf(glm::value_ptr(mv_mat4));

			// draw all
			DrawScene(mv_mat4);
		}

		// Swap front and back buffers 
		// Calls glFlush() inside
		glfwSwapBuffers(globals.window);

		// Check OpenGL errors
		gl_check_error();

		// Poll for and process events
		glfwPollEvents();
	}
}

static void init_mesh(void)
{
	mesh_circle = gen_mesh_circle(1.0f, circle_segments);
	std::cout << "Mesh: CIRCLE initialized, vertices: " << mesh_circle.vertices.size() << ", indices: " << mesh_circle.indices.size() << std::endl;

	// height map
	// nacitani ze souboru zde!
	{
		std::string hm_file("resources/heights.png");
		cv::Mat hmap = cv::imread(hm_file, cv::IMREAD_GRAYSCALE);

		if (hmap.empty())
		{
			std::cerr << "ERR: Height map empty? File:" << hm_file << std::endl;
		}

		height_map = HeightMap(hmap, 10); //image, step size
		std::cout << "Note: height map vertices: " << height_map.vertices.size() << std::endl;
		height_map.textureID = minecraftTex;
		height_map.texture_used = true;
	}

}

static void init(void)
{
	Avatar.posX = 5000.0;
	Avatar.posY = 500.0;
	Avatar.posZ = 5000.0;
	Avatar.yaw = -130;
	Avatar.movementSpeed = 25.0f;
	init_opengl();
	

	// skybox
	skybox.init();
	
#pragma region Textures

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH); //antialiasing
	glEnable(GL_LINE_SMOOTH);

	glPolygonMode(GL_FRONT, GL_FILL);           // mode for model draw...

	// scene contains semi-transparent objects
	
	glPolygonMode(GL_BACK, GL_FILL);            // both front and back (necessary for transparent objects)
	glDisable(GL_CULL_FACE);
	

	// ALL objects are non-transparent 
	// glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // hint for texture mapping 

	woodenBox = textureInit("resources/box.png", false, false);
	minecraftTex = textureInit("resources/tex.png", false, true);
#pragma endregion
	init_mesh();
}

int main(int argc, char* argv[])
{

	init();

	app_loop();

	finalize(EXIT_SUCCESS);

}

//OpenGL
static void init_opengl(void)
{
	init_glfw();
	init_glew();
	init_lights();
	gl_print_info();
}

