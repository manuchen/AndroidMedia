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
	// glfw: initialize and configure//glfw初始化
	// ------------------------------
	glfwInit();
	//声明版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	//glfw创建窗口											
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//显示窗口
	glfwMakeContextCurrent(window);
	//设置窗口宽度高度回调,当窗口大小调整后将调用该回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// glad初始化
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	//顶点着色器
	//opengl已经写了一个顶点着色器源码（储存在一个C的字符串中），但是为了能够让OpenGL使用它，我们必须在运行时动态编译它的源码
	//用glCreateShader创建这个着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//把这个着色器源码附加到着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//然后编译它
	glCompileShader(vertexShader);
	// check for shader compile errors

	//校验着色器是否编译成功
	int success;
	char infoLog[512];//存储错误log
	//用glGetShaderiv检查是否编译成功。如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它。
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	//片段着色器
	//使用GL_FRAGMENT_SHADER常量作为着色器类型,其他创建的用法类似顶点着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//把这个着色器源码附加到着色器对象上
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//然后编译它
	glCompileShader(fragmentShader);
	// check for shader compile errors
	//校验着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders 链接上着色器
	//glCreateProgram函数创建一个程序，并返回新创建程序对象的ID引用。
	int shaderProgram = glCreateProgram();
	//把之前编译的着色器附加到程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//用glLinkProgram链接它们
	glLinkProgram(shaderProgram);
	// check for linking errors
	//检测链接着色器程序是否失败，并获取相应的日志;
	//用glGetProgramiv,glGetProgramInfoLog而不是着色器的
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//删除着色器对象，我们不再需要它们
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};
	// -----------------------------------------------------------------
	float vertices2[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	// -----------------------------------------------------------------


	unsigned int VBO, VAO;
	//创建一个VAO
	glGenVertexArrays(1, &VAO);
	//用glGenBuffers函数和一个缓冲ID生成一个VBO对象
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//// 1.用glBindVertexArray绑定VAO
	//glBindVertexArray(VAO);
	//// 2. 把顶点数组复制到缓冲中供OpenGL使用
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3. 设置顶点属性指针
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	////用glEnableVertexAttribArray，以顶点属性位置值作为参数，启用顶点属性.默认禁用
	//glEnableVertexAttribArray(0);



	// ------------------------------------------------------------
	// 1. 绑定顶点数组对象
	glBindVertexArray(VAO);
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ------------------------------------------------------------

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//调用glVertexAttribPointer将VBO注册为顶点属性的绑定顶点缓冲区对象，所以之后我们可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//取消注释此调用以绘制线框多边形。
	//使用线框模式来绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// 使用循环达到循环渲染效果
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		//自定义输入事件
		// -----
		processInput(window);

		// render
		//渲染指令
		// ------
		//glClearColor来设置清空屏幕所用的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//调用glClear函数来清空屏幕的颜色缓冲;GL_COLOR_BUFFER_BIT---只清空颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		//画我们第一个三角形
		//调用glUseProgram函数，用刚创建的程序对象作为它的参数，以激活这个程序对象
		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time 

		//画我们第二个图形
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)// 检查并调用事件，交换缓冲
		//交互缓冲区，否则显示空白
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		//输入输出事件,否则无法对窗口进行交互
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	//终止渲染 关闭并清理glfw本地资源
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