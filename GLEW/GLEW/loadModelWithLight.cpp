//#include <string>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <SOIL.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Shader.h"
//#include "Camera.h"
//#include "Model.h"
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
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "opengl", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//	glViewport(0, 0, screenWidth, screenHeight);
//	glEnable(GL_DEPTH_TEST);
//
//	Shader shader("model_loading.vs", "model_loading.frag");
//	Shader lampShader("lamp.vs", "lamp.frag");
//
//	Model ourModel("./nanosuit/nanosuit.obj");
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
//	glm::vec3 pointLightPositions[] = {
//		glm::vec3(2.3f, -1.6f, -3.0f),
//		glm::vec3(-1.7f, 0.9f, 1.0f)
//	};
//
//	GLuint VBO, EBO, lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
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
//		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		
//		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//		glUniform3f(glGetUniformLocation(shader.Program, "viewPosition"), camera.Position.x, camera.Position.y, camera.Position.z);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].linear"), 0.009);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].quadratic"), 0.0032);
//		// Point light 2
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
//		glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].linear"), 0.009);
//		glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].quadratic"), 0.0032);
//
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
//		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		ourModel.Draw(shader);
//
//		lampShader.use();
//		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//		glBindVertexArray(lightVAO);
//		GLuint i = 0;
//		for (i = 0; i < 2; i++)
//		{
//			model = glm::mat4();
//			model = glm::translate(model, pointLightPositions[i]);
//			model = glm::scale(model, glm::vec3(0.2f));//make it smaller
//			glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
//
//#pragma endregion