#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 apos;\n"
"void main()\n"
"{\n"
"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	// Initialize glfw
	glfwInit();

	//give hint to glfw about the version of OpenGL
	//since current versio of openGL we're using 3.3 so, major and minor are passed as 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//give hint about which openGL profile (package of fucntions) we're using.
	//CORE - contains all Modern functions
	//Compatibility - contains modern as well as outdated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vertice of a triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.f
	};

	// window specifications
	// DataType of windows object in GLFW
	// template : glfwCreateWindow(width,Height,"name",full_screen_or_not,not important)
	GLFWwindow* window = glfwCreateWindow(800, 800, "graphics", NULL, NULL);

	//error checking if window failed to create
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//introduce the window into current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//tell OpenGL about the area of our viewport for openGL to render in
	// in this case viewport goes from x = 0 , y = 0 to x=800, y=800
	// 0,0 is co-ordinate of bottom left corner of the window
	//800,800 is co-ordinate of top right corner of window as the height of window is 800 as specified earlier
	glViewport(0, 0, 800, 800);

	//GLuint is OpenGL Version of (unSigned) Positive interger 
	// making a vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//making a fragement shader
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//wrap both vertex and fragment shader into one
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//deleting shaders we created previously as they are already in the program now
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//vetex array object, vertex buffer object where we'll store vertex wrapup

	// VAO must be defined prior to VBO

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	//giving 1 as argument cause we'have only one object
	glGenBuffers(1, &VBO);
	//bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* to store our vetices in VBO
	  template for glBufferData

	  glBufferData(type_of_buffer, size-of-data-in-bytes, vertices, GL_STREAM/GL_STATIC/GL_DYNAMIC)
		GL_STREAM - MODIFIED ONCE AND USED A FEW TIMES
		GL_STATIC - MODIFIED ONCE AND USED MANY MANY TIMES
		GL_DYNAMIC - MODIFIED MULTIPLE TIMES AND USED MANY MANY TIMES
		THESE ARE SPECIFIED TO IMPORVE PERFORMANCE
		_DRAW -VERTICES WILL BE MODIFIED AND USED TO DRAW ON SCREEN
		_READ or _COPY */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//timestampe 26:00 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//not mandatory but nice to have to ensure you don't accidentally change VAO or VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);





	//telling openGL to prepare to clear the default color of the buffer and display the new/desired color
	// first 3 are RBG format of color
	//last one is alpha number which dictates transparency of color : 1-Opaque; 0-Transparent
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// tell openGL to execute the command we've told it to prepare for
	glClear(GL_COLOR_BUFFER_BIT);

	//at this point we've BACK Buffer with our Desired color and Front Buffer with Default One
	// so we swap the buffers to see our Color as only pixels of front buffer are seen
	glfwSwapBuffers(window);



	// choose when to close the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//(what-to-draw, starting-vertex, no. of vertices)
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// telling glfw to process all the operations performed on window
		glfwPollEvents();
	}

	//delete all created objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// deleted window after its work is done
	glfwDestroyWindow(window);
	//terminate glfw
	glfwTerminate();
	return 0;
}