//#include <iostream>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//const GLchar* vertexShaderSource = //顶点着色器的源码，接受三个维度的向量的输入，顶点属性为location
//"#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"void main()\n"
//"{ gl_Position = vec4(position.x, position.y, position.z,1.0); }\0";
//
//const GLchar* fragmentShaderSource = //片段着色器的源码，默认为橙色
//"#version 330 core\n"
//"out vec4 color;\n"
//"void main()\n"
//"{ color = vec4(1.0f, 0.5f, 0.2f, 1.0f); }\0";
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
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//绑定源码
//	glCompileShader(vertexShader);//编译着色器
//
//	GLint success;//编译是否成功的标志
//	GLchar infoLog[512];//如果出错的错误信息
//
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检验是否编译成功
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "error: shader vertex compilation failed\n" << infoLog << std::endl;
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
//		std::cout << "error: shader fragment compilation failed\n" << infoLog << std::endl;
//	}
//
//	GLuint shaderProgram = glCreateProgram();//创建着色器程序
//	glAttachShader(shaderProgram, vertexShader);//绑定顶点着色器
//	glAttachShader(shaderProgram, fragmentShader);//绑定片段着色器
//	glLinkProgram(shaderProgram);//链接着色器程序
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "error: shader program compilation failed\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);//删除着色器
//	glDeleteShader(fragmentShader);
//
//	GLfloat vertices[] = {//图形中的顶点
//		0.5f, 0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.5f, -0.5f, 0.0f,
//		-0.5f, 0.5f, 0.0f
//	};
//
//	GLint indices[] = {//创建三角形的顶点的索引
//		0, 1, 3,
//		1, 2, 3
//	};
//
//	GLuint VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);//生成顶点数组对象
//	glGenBuffers(1, &VBO);//生成顶点缓冲对象
//	glGenBuffers(1, &EBO);//生成索引缓冲对象
//
//	glBindVertexArray(VAO);//绑定顶点数组对象，任何随后的顶点属性调用都会存储在这个VAO中
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//复制顶点数组到VBO缓冲中，任何随后的缓冲函数都会用来配置当前绑定的缓冲
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//复制索引数据到缓冲里
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);//设置顶点属性，链接到VBO缓冲
//	//第一个参数指的是哪一个顶点属性，也就是在顶点着色器源码中顶点属性location的值
//	glEnableVertexAttribArray(0);//开启该顶点属性
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑VBO
//	glBindVertexArray(0);//解绑VAO，绘制时需要再次绑定
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		//由于VAO可以保存EBO的绑定状态，因此只要不在上面解绑EBO，这里就可以不用再绑定EBO
//		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//开启线框模式
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
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