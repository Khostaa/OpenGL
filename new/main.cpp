#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>


int main()
{
	//	Initialize GLFW
	glfwInit();

	// telling GLFW that we're using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//telling GLFW that we want to use core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// (width, height, name_of_window, NULL, NULL) 
	// last two parameters can be ignored
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);



	return 0;
}