// a1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main(void)
{
	GLFWwindow* window;
	//extern GuiContext GC;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 320, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	Gui_Init(window);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		COLORREF bc = { 1.0,1.0,0.0 };
		if (Button(window, 1, 10, 10, 50, 20, bc))
			printf("pressed!");
		Render();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}