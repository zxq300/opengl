//#include <iostream>
//#include <cmath>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Shader.h"
//#include "camera.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xposition, double yposition);
//void scroll_callback(GLFWwindow* window, double extra, double scrolloffset);
//void do_movement();
//
//const GLuint WIDTH = 1800, HEIGHT = 1200;
//
//Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
//GLfloat lastX = WIDTH / 2.0;
//GLfloat lastY = HEIGHT / 2.0;
//bool    keys[1024];
//
//glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//
//bool firstMouse = true;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "opengl", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//	glViewport(0, 0, WIDTH, HEIGHT);
//	glEnable(GL_DEPTH_TEST);
//
//	Shader lightingShader("lighting2.vs", "lighting2.frag");
//	Shader lampShader("lamp.vs", "lamp.frag");
//
//	GLfloat vertices[] = {
//		// Positions
//		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
//		-0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
//		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
//
//		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
//		0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
//
//		-0.5f,  0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
//
//		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
//		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,
//		0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,
//	};
//	GLuint indices[] = {
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
//	GLuint VBO, EBO, containerVAO;
//	glGenVertexArrays(1, &containerVAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(containerVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
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
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		lightingShader.use();
//		GLint lightPositionLocation = glGetUniformLocation(lightingShader.Program, "light.position");
//		GLint lightAmbientLocation = glGetUniformLocation(lightingShader.Program, "light.ambient");
//		GLint lightDiffuseLocation = glGetUniformLocation(lightingShader.Program, "light.diffuse");
//		GLint lightSpecularLocation = glGetUniformLocation(lightingShader.Program, "light.specular");
//		GLint materialAmbientLocation = glGetUniformLocation(lightingShader.Program, "material.ambient");
//		GLint materialDiffuseLocation = glGetUniformLocation(lightingShader.Program, "material.diffuse");
//		GLint materialSpecularLocation = glGetUniformLocation(lightingShader.Program, "material.specular");
//		GLint materialShininessLocation = glGetUniformLocation(lightingShader.Program, "material.shininess");
//		GLint viewPositionLocation = glGetUniformLocation(lightingShader.Program, "viewPosition");
//
//		glm::vec3 lightColor;
//		lightColor.x = sin(glfwGetTime() * 2.0f);
//		lightColor.y = sin(glfwGetTime() * 0.7f);
//		lightColor.z = sin(glfwGetTime() * 1.3f);
//		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
//		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
//
//		glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
//		glUniform3f(lightAmbientLocation, ambientColor.x, ambientColor.y, ambientColor.z);
//		glUniform3f(lightDiffuseLocation, diffuseColor.x, diffuseColor.y, diffuseColor.z);
//		glUniform3f(lightSpecularLocation, 1.0f, 1.0f, 1.0f);
//		glUniform3f(materialAmbientLocation, 1.0f, 0.5f, 0.31f);
//		glUniform3f(materialDiffuseLocation, 1.0f, 0.5f, 0.31f);
//		glUniform3f(materialSpecularLocation, 0.5f, 0.5f, 0.5f);
//		glUniform1f(materialShininessLocation, 32.0f);
//		glUniform3f(viewPositionLocation, camera.Position.x, camera.Position.y, camera.Position.z);
//
//		glm::mat4 view;
//		glm::mat4 projection;
//		glm::mat4 model;
//
//		view = camera.GetViewMatrix();
//		projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//
//		GLint modelLocation = glGetUniformLocation(lightingShader.Program, "model");
//		GLint viewLocation = glGetUniformLocation(lightingShader.Program, "view");
//		GLint projectionLocation = glGetUniformLocation(lightingShader.Program, "projection");
//
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(containerVAO);
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		lampShader.use();
//
//		modelLocation = glGetUniformLocation(lampShader.Program, "model");
//		viewLocation = glGetUniformLocation(lampShader.Program, "view");
//		projectionLocation = glGetUniformLocation(lampShader.Program, "projection");
//		model = glm::mat4();
//		model = glm::translate(model, lightPosition);
//		model = scale(model, glm::vec3(0.2f));
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(lightVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//
//	return 0;
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