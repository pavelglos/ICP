#include "OpenGL.h"
#include <glm/gtc/type_ptr.hpp>

bool isFullScreen = false;

void init_glfw(void)
{
	//
	// GLFW init.
	//
	

		// set error callback first
	glfwSetErrorCallback(error_callback);
	

	//initialize GLFW library
	int glfw_ret = glfwInit();
	if (!glfw_ret)
	{
		std::cerr << "GLFW init failed." << std::endl;
		finalize(EXIT_FAILURE);
	}

	// Shader based, modern OpenGL (3.3 and higher)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // only new functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // only old functions (for old tutorials etc.)

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	globals.window = glfwCreateWindow(800, 600, "OpenGL context", NULL, NULL);
	if (!globals.window)
	{
		std::cerr << "GLFW window creation error." << std::endl;
		finalize(EXIT_FAILURE);
	}

	// Get some GLFW info.
	{
		int major, minor, revision;

		glfwGetVersion(&major, &minor, &revision);
		std::cout << "Running GLFW " << major << '.' << minor << '.' << revision << std::endl;
		std::cout << "Compiled against GLFW " << GLFW_VERSION_MAJOR << '.' << GLFW_VERSION_MINOR << '.' << GLFW_VERSION_REVISION << std::endl;
	}

	glfwSetKeyCallback(globals.window, key_callback);
	glfwSetFramebufferSizeCallback(globals.window, fbsize_callback);			// On window resize callback.
	glfwSetMouseButtonCallback(globals.window, mouse_button_callback);
	glfwSetCursorPosCallback(globals.window, cursor_position_callback);

	glfwMakeContextCurrent(globals.window);										// Set current window.
	glfwGetFramebufferSize(globals.window, &globals.width, &globals.height);	// Get window size.
	glfwSwapInterval(0);														// Set V-Sync OFF.
	// glfwSwapInterval(1);														// Set V-Sync ON.

	fbsize_callback(globals.window, globals.width, globals.height);

	globals.app_start_time = glfwGetTime();										// Get start time.
	
}

void init_glew(void)
{
	//
	// Initialize all valid GL extensions with GLEW.
	// Usable AFTER creating GL context!
	//
	{
		GLenum glew_ret;
		glew_ret = glewInit();
		if (glew_ret != GLEW_OK)
		{
			std::cerr << "WGLEW failed with error: " << glewGetErrorString(glew_ret) << std::endl;
			finalize(EXIT_FAILURE);
		}
		else
		{
			std::cout << "GLEW successfully initialized to version: " << glewGetString(GLEW_VERSION) << std::endl;
		}

		// Platform specific. (Change to GLXEW or ELGEW if necessary.)
		glew_ret = wglewInit();
		if (glew_ret != GLEW_OK)
		{
			std::cerr << "WGLEW failed with error: " << glewGetErrorString(glew_ret) << std::endl;
			finalize(EXIT_FAILURE);
		}
		else
		{
			std::cout << "WGLEW successfully initialized platform specific functions." << std::endl;
		}
	}
}

void init_lights(void)
{
	// const glm::vec3 dark_grey(0.67f, 0.67f, 0.67f);
	
	const glm::vec3 dark_grey(0.3f, 0.3f, 0.3f);

	const GLfloat sun_color[] = { 0.67f, 0.67f, 0.67f };

	//lighting model setup
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(dark_grey));  //colour of default ambient light
	
	glShadeModel(GL_SMOOTH);   //Gouraud shading
	glEnable(GL_NORMALIZE);    //normalisation of EVERYTHING! Slower, but safe. 
	glEnable(GL_LIGHTING);
	
	// slunce
	{
		const GLfloat light_position[] = { 0.0f, 0.0f, 4500.0f, 0.0f };
		const GLfloat light_direction[] = { 0.0f, 0.0f, -1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_color);
		glEnable(GL_LIGHT0);
	}

	{
		const GLfloat light_position[] = { 0.0f, 0.0f, -4500.0f, 0.0f };
		const GLfloat light_direction[] = { 0.0f, 0.0f, 1.0f };

		glLightfv(GL_LIGHT1, GL_POSITION, light_position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, sun_color);
		glEnable(GL_LIGHT1);
	}

	{
		const GLfloat light_position[] = { 4500.0f, 0.0f, 0.0f, 0.0f };
		const GLfloat light_direction[] = { -1.0f, 0.0f, 0.0f };

		glLightfv(GL_LIGHT2, GL_POSITION, light_position);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, sun_color);
		glEnable(GL_LIGHT2);
	}

	{
		const GLfloat light_position[] = { -4500.0f, 0.0f, 0.0f, 0.0f };
		const GLfloat light_direction[] = { 1.0f, 0.0f, 0.0f };

		glLightfv(GL_LIGHT3, GL_POSITION, light_position);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_direction);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, sun_color);
		glEnable(GL_LIGHT3);
	}

	//more lighting setup...
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void gl_print_info(void)
{
	// Get OpenGL driver info
	{
		const char* vendor_s = (const char*)glGetString(GL_VENDOR);
		const char* renderer_s = (const char*)glGetString(GL_RENDERER);
		const char* version_s = (const char*)glGetString(GL_VERSION);
		const char* glsl_s = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		std::cout << "OpenGL driver vendor: " << (vendor_s == nullptr ? "<UNKNOWN>" : vendor_s) << ", renderer: " << (renderer_s == nullptr ? "<UNKNOWN>" : renderer_s) << ", version: " << (version_s == nullptr ? "<UNKNOWN>" : version_s) << std::endl;

		GLint profile_flags;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile_flags);
		std::cout << "Current profile: ";
		if (profile_flags & GL_CONTEXT_CORE_PROFILE_BIT)
			std::cout << "CORE";
		else
			std::cout << "COMPATIBILITY";
		std::cout << std::endl;

		GLint context_flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
		std::cout << "Active context flags: ";
		if (context_flags & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
			std::cout << "GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT ";
		if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
			std::cout << "GL_CONTEXT_FLAG_DEBUG_BIT ";
		if (context_flags & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT)
			std::cout << "GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT ";
		if (context_flags & GL_CONTEXT_FLAG_NO_ERROR_BIT)
			std::cout << "GL_CONTEXT_FLAG_NO_ERROR_BIT";
		std::cout << std::endl;

		std::cout << "Primary GLSL shading language version: " << (glsl_s == nullptr ? "<UNKNOWN>" : glsl_s) << std::endl;
	}

	//
	// GLM & GLI library
	//

	std::cout << "GLM version: " << GLM_VERSION_MAJOR << '.' << GLM_VERSION_MINOR << '.' << GLM_VERSION_PATCH << "rev" << GLM_VERSION_REVISION << std::endl;
	std::cout << "GLI version: " << GLI_VERSION_MAJOR << '.' << GLI_VERSION_MINOR << '.' << GLI_VERSION_PATCH << "rev" << GLI_VERSION_REVISION << std::endl;
}


void finalize(int code)
{
	cv::destroyAllWindows();

	// Close OpenGL window if opened and terminate GLFW  
	if (globals.window)
		glfwDestroyWindow(globals.window);
	glfwTerminate();

	exit(code);
}

static void error_callback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if ((action == GLFW_PRESS) || (action == GLFW_REPEAT))
	{
		const GLFWvidmode* pWindowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			avatarMoveForward();
			break;
		case GLFW_KEY_S:
			avatarMoveBackward();
			break;
		case GLFW_KEY_A:
			avatarMoveLeft();
			break;
		case GLFW_KEY_D:
			avatarMoveRight();
			break;
		case GLFW_KEY_E:
			Avatar.yaw += 0.75f;
			break;
		case GLFW_KEY_Q:
			Avatar.yaw -= 0.75f;
			break;
		case GLFW_KEY_F11:
			isFullScreen = !isFullScreen;
			if (isFullScreen) {
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, pWindowMode->width, pWindowMode->height, GLFW_DONT_CARE);
			}
			else {
				glfwSetWindowMonitor(window, NULL, 0, 0, pWindowMode->width, pWindowMode->height, GLFW_DONT_CARE);
				glfwSetWindowSize(window, 800, 600);
				glfwSetWindowPos(window, 100, 100);
			}
			
			
			break;
		default:
			break;
		}
	}
}

static void fbsize_callback(GLFWwindow* window, int width, int height)
{
	// check for limit case (prevent division by 0)
	if (height == 0) height = 1;

	float ratio = width * 1.0f / height;

	globals.width = width;
	globals.height = height;

	glMatrixMode(GL_PROJECTION);				// set projection matrix for following transformations

	//glLoadIdentity();							// clear all transformations
	//glOrtho(0, width, 0, height, -1000, 1000);  // set Orthographic projection
	//glScalef(1, -1, 1);							// invert Y-axis, so that values decrease in downwards direction to be same as OS coordinates
	//glTranslatef(0, -height, 0);				// shift the origin to bottom left corner 

	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		ratio,			     // Aspect Ratio. Depends on the size of your window.
		0.1f,                // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		20000.0f              // Far clipping plane. Keep as little as possible.
	);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));

	glViewport(0, 0, width, height);			// set visible area

	std::cout << width << " " << height << std::endl;
}

//---------------------------------------------------------------------
// Mouse pressed?
//---------------------------------------------------------------------
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			avatarMoveUp();			
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			avatarMoveDown();			
		}
	}
}

//---------------------------------------------------------------------
// Mose moved?
//---------------------------------------------------------------------
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static int first = true;
	static int old_x;
	static int old_y;
	
	if (first) {
		old_x = xpos;
		old_y = ypos;
		first = false;
	}
	
	float xoffset = xpos - old_x;
	float yoffset = old_y - ypos;
	old_x = xpos;
	old_y = ypos;
	
	// pridana sensitivita
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Avatar.yaw += xoffset;
	Avatar.pitch += yoffset;

	
	if (Avatar.pitch > 89.0f)
		Avatar.pitch = 89.0f;

	if (Avatar.pitch < -89.0f)
		Avatar.pitch = -89.0f;
		
}
