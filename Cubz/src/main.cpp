#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "vec.h"
#include "window.h"
#include "input.h"
#include "entity.h"
#include "mesh_render.h"

void error_callback(int error, const char* description)
{
	std::cout << "glfw error : " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::instance.onKeyEvent(key, action);
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input::instance.onMouseMoved(xpos, ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Input::instance.onButtonEvent(button, action);
}

int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		std::cout << "glfw init failed" << std::endl;
	}
	std::cout << "glfw init success" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(error_callback);

	double lastFrameTime = glfwGetTime();

	Window* window = new Window("Cubz", ivec2(800, 600));
	window->open();


	glfwSetKeyCallback(window->glwfWindow(), keyCallback);
	glfwSetMouseButtonCallback(window->glwfWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(window->glwfWindow(), cursorPositionCallback);
	while (window->isOpen())
	{
		Input::instance.update();
		double currentTime = glfwGetTime();
		window->update(currentTime - lastFrameTime);
		window->render();

		double wait_time = 1.0 / (60);

		if (currentTime - lastFrameTime < wait_time)
		{
			double dur = (wait_time - (currentTime - lastFrameTime));
			Sleep((DWORD)(dur * 1000.0 + 0.5));
		}

		lastFrameTime = currentTime;
	}
	window->close();
	delete window;
	glfwTerminate();
}
