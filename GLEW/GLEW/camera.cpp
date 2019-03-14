//#include <iostream>
//#include <cmath>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "Shader.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//GLfloat mixValue = 0.5f;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "opengl", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, key_callback);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	glEnable(GL_DEPTH_TEST);
//
//	Shader ourShader("coordinate.vs", "coordinate.frag");
//
//	GLfloat vertices[] = {
//		// Positions          // Texture Coords
//		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, //0
//		0.5f, -0.5f, 0.5f,   1.0f, 1.0f, //1
//		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f,//2
//		-0.5f,  0.5f, 0.5f,   0.0f, 0.0f,//3
//
//		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f,//4
//		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f,//5
//		0.5f, -0.5f, -0.5f,   0.0f, 1.0f, //6
//		0.5f,  0.5f, -0.5f,   0.0f, 0.0f, //7
//
//		0.5f,  0.5f, -0.5f,   1.0f, 0.0f,//8
//		0.5f, -0.5f, -0.5f,   1.0f, 1.0f,//9
//		0.5f, -0.5f, 0.5f,   0.0f, 1.0f,//10
//		0.5f,  0.5f, 0.5f,   0.0f, 0.0f,//11
//
//		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, //12
//		-0.5f, -0.5f, 0.5f,   1.0f, 1.0f, //13
//		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,//14
//		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f,//15
//
//		0.5f, 0.5f, -0.5f,   1.0f, 0.0f, //16
//		0.5f, 0.5f, 0.5f,   1.0f, 1.0f,  //17
//		-0.5f, 0.5f, 0.5f,   0.0f, 1.0f, //18
//		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f,//19
//
//		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f,//20
//		-0.5f, -0.5f, 0.5f,   1.0f, 1.0f, //21
//		0.5f, -0.5f, 0.5f,   0.0f, 1.0f,  //22
//		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, //23
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
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f,  0.0f,  0.0f),
//		glm::vec3(2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f,  2.0f, -2.5f),
//		glm::vec3(1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	GLuint VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint texture1, texture2;
//
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height;
//	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	image = SOIL_load_image("container2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		GLint textureLocation1 = glGetUniformLocation(ourShader.Program, "ourTexture1");
//		glUniform1i(textureLocation1, 0);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//		GLint textureLocation2 = glGetUniformLocation(ourShader.Program, "ourTexture2");
//		glUniform1i(textureLocation1, 1);
//		GLint mixValueLocation = glGetUniformLocation(ourShader.Program, "mixValue");
//		glUniform1f(mixValueLocation, mixValue);
//
//		ourShader.use();
//
//		//glm::mat4 model;
//		glm::mat4 view;
//		glm::mat4 projection;
//		GLfloat radius = 10.0f;
//		GLfloat camX = sin(glfwGetTime()) * radius;
//		GLfloat camZ = cos(glfwGetTime()) * radius;
//		//model = glm::rotate(model, (GLfloat)glfwGetTime() * 5.0f, glm::vec3(0.5f, 1.0f, 0.0f));
//		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//		view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//
//		GLint modelLocation = glGetUniformLocation(ourShader.Program, "model");
//		GLint viewLocation = glGetUniformLocation(ourShader.Program, "view");
//		GLint projectionLocation = glGetUniformLocation(ourShader.Program, "projection");
//
//		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(VAO);
//		//
//		GLuint i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			GLfloat angle = 2.0f * i;
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			model = glm::rotate(model, angle, glm::vec3(1.0f,0.3f,0.5f));
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		}
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glfwTerminate();
//
//	return 0;
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//	{
//		mixValue += 0.1f;
//		if (mixValue >= 1.0f)
//		{
//			mixValue = 1.0f;
//		}
//	}
//	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
//	{
//		mixValue -= 0.1f;
//		if (mixValue <= 0.0f)
//		{
//			mixValue = 0.0f;
//		}
//	}
//}