#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include "Shader.h"
#include "Camera.h"
using namespace std;

GLuint screenWidth = 800, screenHeight = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xposition, double yposition);
void scroll_callback(GLFWwindow* window, double extra, double scrolloffset);
void do_movement();
GLuint loadTexture(char* path, GLboolean alpha);
GLuint loadCubemap(vector<const GLchar*> faces);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;

bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true;
	glewInit();

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Shader shader("advanced.vs", "advanced.frag");
	Shader skyboxShader("skybox.vs", "skybox.frag");

	GLfloat cubeVertices[] = {
		// Positions
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,


		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
		-0.5f,-0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,


		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,-0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f,-0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, 0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,


		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f,-0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f,-0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f
	};

	GLuint cubeIndices[] = {
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10,11,

		12,13,15,
		13,14,15,

		16,17,19,
		17,18,19,

		20,21,23,
		21,22,23
	};

	GLfloat skyboxVertices[] = {
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,


		1.0f,  1.0f, -1.0f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
		-1.0f,-1.0f, -1.0f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,


		1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		1.0f,  1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-1.0f, 1.0f, -1.0f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-1.0f,-1.0f, -1.0f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-1.0f,-1.0f,  1.0f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, 1.0f,  1.0f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-1.0f, 1.0f,  1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		1.0f,  1.0f,  1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,


		1.0f, -1.0f, -1.0f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
		-1.0f,-1.0f,  1.0f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
		-1.0f,-1.0f, -1.0f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f
	};

	GLuint skyboxIndices[] = {
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10,11,

		12,13,15,
		13,14,15,

		16,17,19,
		17,18,19,

		20,21,23,
		21,22,23
	};

	GLuint cubeVAO, cubeVBO, cubeEBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeEBO);

	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), &cubeIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint cubeTexture = loadTexture("box.jpg", false);

	vector<const GLchar*> faces;
	faces.push_back("skybox/right.jpg");
	faces.push_back("skybox/left.jpg");
	faces.push_back("skybox/top.jpg");
	faces.push_back("skybox/bottom.jpg");
	faces.push_back("skybox/back.jpg");
	faces.push_back("skybox/front.jpg");

	GLuint cubemapTexture = loadCubemap(faces);

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glDepthMask(GL_FALSE);//为了保证在移动时天空盒永远在所绘物体的后面，绘制天空盒时要关闭深度测试

		//glDepthMask(GL_TRUE);//绘制完开启

		shader.use();
		glm::mat4 model;
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(cubeVAO);
		glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		
		glBindVertexArray(cubeVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));//去除平移部分，使天空盒与camera保持一致
																	  //glm::mat4 view = camera.GetViewMatrix();
		
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(skyboxShader.Program, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		glBindVertexArray(skyboxVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

GLuint loadTexture(char* path, GLboolean alpha)
{
	GLuint diffuseMap;
	glGenTextures(1, &diffuseMap);
	int width, height;
	unsigned char* image;

	image = SOIL_load_image(path, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return diffuseMap;
}

GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GLuint i = 0;
	for (i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
		
	}
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xposition, double yposition)
{
	if (firstMouse)
	{
		lastX = xposition;
		lastY = yposition;
		firstMouse = false;
	}

	GLfloat xoffset = xposition - lastX;
	GLfloat yoffset = lastY - yposition;
	lastX = xposition;
	lastY = yposition;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double extra, double scrolloffset)
{
	camera.ProcessMouseScroll(scrolloffset);
}
