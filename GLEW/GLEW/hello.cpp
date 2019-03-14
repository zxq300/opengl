/*********************************************
configuration:
glew32.lib, glew32s.lib -> VC\lib
glew32.dll -> System32
glew.h, glxew, wglew -> VC\include\GL

glfw3.lib, glfw3dll.lib -> VC\lib
glfw3.dll -> System32
glfw3.h -> VC\include\GLFW

链接这3个库
glew32s.lib
glfw3.lib
OpenGL32.lib
可以在程序最前面添加
#pragma comment(lib,"***.lib")
或直接在链接器的输入中添加附加依赖项
********************************************/

//#include <iostream>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

//const GLuint WIDTH = 800, HEIGHT = 600;
//
//int main()
//{
//	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
//	// Init GLFW
//	glfwInit();
//	// Set all the required options for GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	// Create a GLFWwindow object that we can use for GLFW's functions
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
//	glewExperimental = GL_TRUE;
//	// Initialize GLEW to setup the OpenGL Function pointers
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	// Define the viewport dimensions
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	// Game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//		glfwPollEvents();
//		// Swap the screen buffers
//		glfwSwapBuffers(window);
//	}
//
//	// Terminate GLFW, clearing any resources allocated by GLFW.
//	glfwTerminate();
//	return 0;
//}