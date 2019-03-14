//#include <iostream>
//#include <cmath>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//const GLint WIDTH = 800, HEIGHT = 600;
//
//const GLchar* vertexShaderSource =
//"#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"layout (location = 1) in vec3 color;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(position, 1.0);\n"
//"ourColor = color;\n"
//"}\0";
//
//const GLchar* fragmentShaderSource =
//"#version 330 core\n"
//"in vec3 ourColor;\n"
//"out vec4 color;\n"
//"void main()\n"
//"{\n"
//"color = vec4(ourColor,1.0f);\n"
//"}\n\0";
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
//
//	glfwSetKeyCallback(window, key_callback);
//
//	glewExperimental = GL_TRUE;
//
//	glewInit();
//
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	GLint success;
//	GLchar infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "error:shader vertex compilation failed\n" << infoLog << std::endl;
//	}
//
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "error:shader fragment compilation failed\n" << infoLog << std::endl;
//	}
//
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "error:shader program linking failed\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	GLfloat vertices[] = {
//		// Positions         // Colors
//		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
//		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
//	};
//
//	GLint indices[] = { 0, 1, 2 };
//
//	GLuint VBO, VAO, EBO;
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);//数据前三个是位置
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));//后三个是颜色
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
//
//	return 0;
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//}