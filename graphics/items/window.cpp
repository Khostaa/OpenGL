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
		// telling glfw to process all the operations performed on window
		glfwPollEvents();
	}

	// deleted window after its work is done
	glfwDestroyWindow(window);
	//terminate glfw
	glfwTerminate();
	return 0;
}