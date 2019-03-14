//#include <iostream>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//const GLchar* vertexShaderSource = //������ɫ����Դ�룬��������ά�ȵ����������룬��������Ϊlocation
//"#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"void main()\n"
//"{ gl_Position = vec4(position.x, position.y, position.z,1.0); }\0";
//
//const GLchar* fragmentShaderSource = //Ƭ����ɫ����Դ�룬Ĭ��Ϊ��ɫ
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
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//������ɫ��
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//��Դ��
//	glCompileShader(vertexShader);//������ɫ��
//
//	GLint success;//�����Ƿ�ɹ��ı�־
//	GLchar infoLog[512];//�������Ĵ�����Ϣ
//
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//�����Ƿ����ɹ�
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
//	GLuint shaderProgram = glCreateProgram();//������ɫ������
//	glAttachShader(shaderProgram, vertexShader);//�󶨶�����ɫ��
//	glAttachShader(shaderProgram, fragmentShader);//��Ƭ����ɫ��
//	glLinkProgram(shaderProgram);//������ɫ������
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "error: shader program compilation failed\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);//ɾ����ɫ��
//	glDeleteShader(fragmentShader);
//
//	GLfloat vertices[] = {//ͼ���еĶ���
//		0.5f, 0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.5f, -0.5f, 0.0f,
//		-0.5f, 0.5f, 0.0f
//	};
//
//	GLint indices[] = {//���������εĶ��������
//		0, 1, 3,
//		1, 2, 3
//	};
//
//	GLuint VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);//���ɶ����������
//	glGenBuffers(1, &VBO);//���ɶ��㻺�����
//	glGenBuffers(1, &EBO);//���������������
//
//	glBindVertexArray(VAO);//�󶨶�����������κ����Ķ������Ե��ö���洢�����VAO��
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���ƶ������鵽VBO�����У��κ����Ļ��庯�������������õ�ǰ�󶨵Ļ���
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//�����������ݵ�������
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);//���ö������ԣ����ӵ�VBO����
//	//��һ������ָ������һ���������ԣ�Ҳ�����ڶ�����ɫ��Դ���ж�������location��ֵ
//	glEnableVertexAttribArray(0);//�����ö�������
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);//���VBO
//	glBindVertexArray(0);//���VAO������ʱ��Ҫ�ٴΰ�
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
//		//����VAO���Ա���EBO�İ�״̬�����ֻҪ����������EBO������Ϳ��Բ����ٰ�EBO
//		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����߿�ģʽ
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