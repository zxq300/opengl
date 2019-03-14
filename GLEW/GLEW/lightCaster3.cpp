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
//const GLuint WIDTH = 800, HEIGHT = 600;
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
////这是聚光灯
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
//	Shader lightingShader("lighting4.vs", "lighting6.frag");
//	Shader lampShader("lamp.vs", "lamp.frag");
//
//	GLfloat vertices[] = {
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
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	GLuint diffuseMap, specularMap, emissionMap;
//	glGenTextures(1, &diffuseMap);
//	glGenTextures(1, &specularMap);
//	glGenTextures(1, &emissionMap);
//	int width, height;
//	unsigned char* image;
//
//	image = SOIL_load_image("container3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	image = SOIL_load_image("container3_side.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, specularMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	image = SOIL_load_image("container3_emission.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, emissionMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	lightingShader.use();
//	GLint materialDiffuseLocation = glGetUniformLocation(lightingShader.Program, "material.diffuse");//漫反射贴图
//	glUniform1i(materialDiffuseLocation, 0);
//	GLint materialSpecularLocation = glGetUniformLocation(lightingShader.Program, "material.specular");
//	glUniform1i(materialSpecularLocation, 1);
//	GLint materialEmissionLocation = glGetUniformLocation(lightingShader.Program, "material.emission");
//	glUniform1i(materialEmissionLocation, 2);
//	GLint materialShininessLocation = glGetUniformLocation(lightingShader.Program, "material.shininess");
//	glUniform1f(materialShininessLocation, 64.0f);
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
//		GLint lightDirectionLocation = glGetUniformLocation(lightingShader.Program, "light.direction");
//		GLint lightAmbientLocation = glGetUniformLocation(lightingShader.Program, "light.ambient");
//		GLint lightDiffuseLocation = glGetUniformLocation(lightingShader.Program, "light.diffuse");
//		GLint lightSpecularLocation = glGetUniformLocation(lightingShader.Program, "light.specular");
//		GLint lightCutOffLocation = glGetUniformLocation(lightingShader.Program, "light.cutOff");
//		GLint lightOuterCutOffLocation = glGetUniformLocation(lightingShader.Program, "light.outerCutOff");
//		GLint viewPositionLocation = glGetUniformLocation(lightingShader.Program, "viewPosition");
//
//		//glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
//		glUniform3f(lightPositionLocation, camera.Position.x, camera.Position.y, camera.Position.z);
//		//glUniform3f(lightDirectionLocation, -0.2f, -1.0f, -0.3f);
//		glUniform3f(lightDirectionLocation, camera.Front.x, camera.Front.y, camera.Front.z);
//		glUniform3f(lightAmbientLocation, 0.2f, 0.2f, 0.2f);
//		glUniform3f(lightDiffuseLocation, 0.5f, 0.5f, 0.5f);
//		glUniform3f(lightSpecularLocation, 1.0f, 1.0f, 1.0f);
//		glUniform1f(lightCutOffLocation, glm::cos(glm::radians(20.0f)));
//		glUniform1f(lightOuterCutOffLocation, glm::cos(glm::radians(25.0f)));
//		glUniform3f(viewPositionLocation, camera.Position.x, camera.Position.y, camera.Position.z);
//
//		GLint lightConstantLocation = glGetUniformLocation(lightingShader.Program, "light.constant");
//		GLint lightLinearLocation = glGetUniformLocation(lightingShader.Program, "light.linear");
//		GLint lightQuadraticLocation = glGetUniformLocation(lightingShader.Program, "light.quadratic");
//
//		glUniform1f(lightConstantLocation, 1.0f);
//		glUniform1f(lightLinearLocation, 0.09f);
//		glUniform1f(lightQuadraticLocation, 0.032f);
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
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, specularMap);
//		//glActiveTexture(GL_TEXTURE2);
//		//glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//		/*glBindVertexArray(containerVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);*/
//
//		glBindVertexArray(containerVAO);
//		GLint i = 0;
//		for (i = 0; i < 10; i++)
//		{
//			model = glm::mat4();
//			model = glm::translate(model, cubePositions[i]);
//			GLfloat angle = 20.0f * i;
//			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		}
//		glBindVertexArray(0);
//
//		/*lampShader.use();
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
//		glBindVertexArray(0);*/
//
//		glBindTexture(GL_TEXTURE_2D, 0);
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