//#include <string>
//#include <map>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <SOIL.h>
//#include "Shader.h"
//#include "Camera.h"
//
//using namespace std;
//
//GLuint screenWidth = 800, screenHeight = 600;
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xposition, double yposition);
//void scroll_callback(GLFWwindow* window, double extra, double scrolloffset);
//void do_movement();
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//
//GLuint loadTexture(char* path, GLboolean alpha);
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "opengl", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	Shader shader("blend.vs", "blend.frag");
//	GLfloat cubeVertices[] = {
//		// Positions
//		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
//		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
//		-0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
//		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
//
//		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
//		-0.5f,-0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
//
//		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
//
//		-0.5f, 0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
//		-0.5f,-0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
//		-0.5f,-0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
//		-0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
//
//		0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//		-0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
//		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
//
//		-0.5f,-0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,
//		-0.5f,-0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f
//	};
//	GLuint cubeIndices[] = {
//		0, 1, 3,
//		1, 2, 3,
//
//		4, 5, 7,
//		5, 6, 7,
//
//		8, 9, 11,
//		9, 10,11,
//
//		12,13,15,
//		13,14,15,
//
//		16,17,19,
//		17,18,19,
//
//		20,21,23,
//		21,22,23
//	};
//
//	GLfloat planeVertices[] = {
//		-5.0f,-0.5f, -5.0f,		0.0f, -1.0f, 0.0f,	2.0f, 0.0f,
//		-5.0f,-0.5f,  5.0f,		0.0f, -1.0f, 0.0f,	2.0f, 2.0f,
//		5.0f, -0.5f,  5.0f,		0.0f, -1.0f, 0.0f,	0.0f, 2.0f,
//		5.0f, -0.5f, -5.0f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f
//	};
//
//	GLuint planeIndices[] = {
//		0, 1, 3,
//		1, 2, 3
//	};
//
//	GLfloat transparentVertices[] = {
//		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
//		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
//		-0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
//		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
//	};
//
//	GLuint transparentIndices[] = {
//		0, 1, 3,
//		1, 2, 3
//	};
//
//	GLuint cubeVAO, cubeVBO, cubeEBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glGenBuffers(1, &cubeEBO);
//
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), &cubeIndices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint planeVAO, planeVBO, planeEBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glGenBuffers(1, &planeEBO);
//
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), &planeIndices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint transparentVAO, transparentVBO, transparentEBO;
//	glGenVertexArrays(1, &transparentVAO);
//	glGenBuffers(1, &transparentVBO);
//	glGenBuffers(1, &transparentEBO);
//
//	glBindVertexArray(transparentVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, transparentEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(transparentIndices), &transparentIndices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint cubeTexture = loadTexture("cubeTexture.jpg", false);
//	GLuint planeTexture = loadTexture("planeTexture.jpg", false);
//	//GLuint transparentTexture = loadTexture("grass.jpg", true);
//	GLuint transparentTexture = loadTexture("blending_transparent_window.jpg", true);
//
//	vector<glm::vec3> vegetation;
//	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
//	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
//	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
//	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
//	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
//
//	while (!glfwWindowShouldClose(window))
//	{
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		glfwPollEvents();
//		
//		do_movement();
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//		
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(-1.0f, 0.01f, -1.0f));
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//
//		glBindVertexArray(cubeVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(2.0f, 0.01f, 0.0f));
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//
//		glBindVertexArray(cubeVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		model = glm::mat4();
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//
//		//glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, planeTexture);
//
//		glBindVertexArray(planeVAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		//glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, transparentTexture);
//
//		/*glBindVertexArray(transparentVAO);
//		for (GLuint i = 0; i < vegetation.size(); i++)
//		{
//			model = glm::mat4();
//			model = glm::translate(model, vegetation[i]);
//			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		}
//		glBindVertexArray(0);*/
//
//		map<float, glm::vec3> sorted;
//		GLuint i = 0;
//		for (i = 0; i < vegetation.size(); i++)
//		{
//			GLfloat distance = glm::length(camera.Position - vegetation[i]);
//			sorted[distance] = vegetation[i];
//		}
//		glBindVertexArray(transparentVAO);
//		map<float, glm::vec3>::reverse_iterator it;
//		for (it = sorted.rbegin(); it != sorted.rend(); ++it)
//		{
//			model = glm::mat4();
//			model = glm::translate(model, it->second);
//			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		}
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//
//	return 0;
//}
//
//GLuint loadTexture(char* path, GLboolean alpha)
//{
//	GLuint diffuseMap;
//	glGenTextures(1, &diffuseMap);
//	int width, height;
//	unsigned char* image;
//
//	image = SOIL_load_image(path, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(image);
//
//	return diffuseMap;
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//		{
//			keys[key] = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			keys[key] = false;
//		}
//		else
//			std::cout << "error:keyboard collision\n" << std::endl;
//	}
//}
//
//void do_movement()
//{
//	if (keys[GLFW_KEY_W])
//	{
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_S])
//	{
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_A])
//	{
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	}
//	if (keys[GLFW_KEY_D])
//	{
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	}
//}
//
//void mouse_callback(GLFWwindow* window, double xposition, double yposition)
//{
//	if (firstMouse)
//	{
//		lastX = xposition;
//		lastY = yposition;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xposition - lastX;
//	GLfloat yoffset = lastY - yposition;
//	lastX = xposition;
//	lastY = yposition;
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double extra, double scrolloffset)
//{
//	camera.ProcessMouseScroll(scrolloffset);
//}
