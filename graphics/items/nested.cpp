#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
	// create a vertex Shader and its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	//Create Fragement shader and its reference
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Fragment Shader Source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	//create Shader Program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	//Attach Vertex and Fragment Shaders to Shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	//deleting the now useless vertes and fragment shaders objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//vertices Coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	//Indices for vertices order
	GLuint indices[] =
	{
		0,3,5, //Lower left triangle
		3,2,4, //Lower right triangle
		5,4,1 //Upper triangle

	};

	//Create reference containers for the Vertex Array Object and the vertex buffer object
	// VAO must be defined prior to VBO

	GLuint VAO, VBO, EBO;
	//GENERATE VAO, VBO and EBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Introduce vetices into the VBO
	  template for glBufferData

	  glBufferData(type_of_buffer, size-of-data-in-bytes, vertices, GL_STREAM/GL_STATIC/GL_DYNAMIC)
		GL_STREAM - MODIFIED ONCE AND USED A FEW TIMES
		GL_STATIC - MODIFIED ONCE AND USED MANY MANY TIMES
		GL_DYNAMIC - MODIFIED MULTIPLE TIMES AND USED MANY MANY TIMES
		THESE ARE SPECIFIED TO IMPORVE PERFORMANCE
		_DRAW -VERTICES WILL BE MODIFIED AND USED TO DRAW ON SCREEN
		_READ or _COPY */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Bind the EBO specifying it's a Gl_Element_array_buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Introduce the indices into EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//timestampe 26:00 
	//Configure the Vertex attribute so that openGl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the vertex attribute so that OpenGl knows how to use it
	glEnableVertexAttribArray(0);

	//not mandatory but nice to have to ensure you don't accidentally change VAO or VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// choose when to close the window
	while (!glfwWindowShouldClose(window))
	{
		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean the back buffer and assing the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//tell OpenGL which shader program we want to use
		glUseProgram(shaderProgram);
		//bind the VAO so OpenGl knows to use it
		glBindVertexArray(VAO);
		//(what-to-draw, no. of indices, datatypeofindices, index of indices)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// telling glfw to process all the operations performed on window
		glfwPollEvents();
	}

	//delete all created objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// deleted window after its work is done
	glfwDestroyWindow(window);
	//terminate glfw
	glfwTerminate();
	return 0;
}