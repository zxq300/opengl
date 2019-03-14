//#include <string>
//#include <algorithm>
//
//using namespace std;
//
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
//GLuint screenWidth = 800, screenHeight = 600;
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xposition, double yposition);
//void scroll_callback(GLFWwindow* window, double extra, double scrolloffset);
//void do_movement();
//
//GLuint loadTexture(char* path, GLboolean alpha);
//GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
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
//	glDepthFunc(GL_LESS);
//
//	Shader shader("depthTest.vs", "depthTest.frag");
//	Shader screenShader("frameBuffer.vs", "frameBuffer.frag");
//
//	GLfloat cubeVertices[] = {
//		// Positions
//		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
//		-0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
//		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
//		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
//
//
//		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
//		-0.5f,-0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
//		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
//
//
//		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
//
//		-0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
//		-0.5f,-0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
//		-0.5f,-0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
//		-0.5f, 0.5f,  0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
//
//		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
//		-0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
//
//
//		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
//		-0.5f,-0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
//		-0.5f,-0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f
//	};
//
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
//	GLfloat quadVertices[] = {
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		-1.0f, -1.0f,  0.0f, 0.0f,
//		1.0f, -1.0f,  1.0f, 0.0f,
//		1.0f,  1.0f,  1.0f, 1.0f
//	};
//
//	GLuint quadIndices[] = {
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
//	GLuint quadVAO, quadVBO, quadEBO;//一个覆盖视窗的长方形
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glGenBuffers(1, &quadEBO);
//
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint cubeTexture = loadTexture("box.jpg", false);
//	GLuint planeTexture = loadTexture("planeTexture.jpg", false);
//
//	GLuint framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	
//	GLuint textureColorbuffer = generateAttachmentTexture(false, false);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
//
//	GLuint rbo;//渲染缓冲对象
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)//check
//		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		glfwPollEvents();
//		do_movement();
//
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glEnable(GL_DEPTH_TEST);
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
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glDisable(GL_DEPTH_TEST);
//
//		screenShader.use();
//		glBindVertexArray(quadVAO);
//		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteFramebuffers(1, &framebuffer);
//
//	glfwTerminate();
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
//GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
//{
//	// What enum to use?
//	GLenum attachment_type;
//	if (!depth && !stencil)
//		attachment_type = GL_RGB;
//	else if (depth && !stencil)
//		attachment_type = GL_DEPTH_COMPONENT;
//	else if (!depth && stencil)
//		attachment_type = GL_STENCIL_INDEX;
//
//	//Generate texture ID and load texture data 
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	if (!depth && !stencil)
//		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, screenWidth, screenHeight, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
//	else // Using both a stencil and depth test, needs special format arguments
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	return textureID;
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
//		
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
