#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	// glfw: initialize and configure//glfw��ʼ��
	// ------------------------------
	glfwInit();
	//�����汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	//glfw��������											
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//��ʾ����
	glfwMakeContextCurrent(window);
	//���ô��ڿ�ȸ߶Ȼص�,�����ڴ�С�����󽫵��øûص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// glad��ʼ��
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	//������ɫ��
	//opengl�Ѿ�д��һ��������ɫ��Դ�루������һ��C���ַ����У�������Ϊ���ܹ���OpenGLʹ���������Ǳ���������ʱ��̬��������Դ��
	//��glCreateShader���������ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//�������ɫ��Դ�븽�ӵ���ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Ȼ�������
	glCompileShader(vertexShader);
	// check for shader compile errors

	//У����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];//�洢����log
	//��glGetShaderiv����Ƿ����ɹ����������ʧ�ܣ����ǻ���glGetShaderInfoLog��ȡ������Ϣ��Ȼ���ӡ����
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	//Ƭ����ɫ��
	//ʹ��GL_FRAGMENT_SHADER������Ϊ��ɫ������,�����������÷����ƶ�����ɫ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//�������ɫ��Դ�븽�ӵ���ɫ��������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Ȼ�������
	glCompileShader(fragmentShader);
	// check for shader compile errors
	//У����ɫ���Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders ��������ɫ��
	//glCreateProgram��������һ�����򣬲������´�����������ID���á�
	int shaderProgram = glCreateProgram();
	//��֮ǰ�������ɫ�����ӵ����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//��glLinkProgram��������
	glLinkProgram(shaderProgram);
	// check for linking errors
	//���������ɫ�������Ƿ�ʧ�ܣ�����ȡ��Ӧ����־;
	//��glGetProgramiv,glGetProgramInfoLog��������ɫ����
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//ɾ����ɫ���������ǲ�����Ҫ����
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//��������
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};
	// -----------------------------------------------------------------
	float vertices2[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	// -----------------------------------------------------------------


	unsigned int VBO, VAO;
	//����һ��VAO
	glGenVertexArrays(1, &VAO);
	//��glGenBuffers������һ������ID����һ��VBO����
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//// 1.��glBindVertexArray��VAO
	//glBindVertexArray(VAO);
	//// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3. ���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	////��glEnableVertexAttribArray���Զ�������λ��ֵ��Ϊ���������ö�������.Ĭ�Ͻ���
	//glEnableVertexAttribArray(0);



	// ------------------------------------------------------------
	// 1. �󶨶����������
	glBindVertexArray(VAO);
	// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. �趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ------------------------------------------------------------

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//����glVertexAttribPointer��VBOע��Ϊ�������Եİ󶨶��㻺������������֮�����ǿ��԰�ȫ�ؽ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//ȡ��ע�ʹ˵����Ի����߿����Ρ�
	//ʹ���߿�ģʽ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// ʹ��ѭ���ﵽѭ����ȾЧ��
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		//�Զ��������¼�
		// -----
		processInput(window);

		// render
		//��Ⱦָ��
		// ------
		//glClearColor�����������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//����glClear�����������Ļ����ɫ����;GL_COLOR_BUFFER_BIT---ֻ�����ɫ����
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		//�����ǵ�һ��������
		//����glUseProgram�������øմ����ĳ��������Ϊ���Ĳ������Լ�������������
		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time 

		//�����ǵڶ���ͼ��
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)// ��鲢�����¼�����������
		//������������������ʾ�հ�
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		//��������¼�,�����޷��Դ��ڽ��н���
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	//��ֹ��Ⱦ �رղ�����glfw������Դ
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}