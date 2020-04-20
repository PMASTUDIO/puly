#include "Window.h"

#include <GL/glew.h>

Window::Window() : m_Window(nullptr)
{
}

Window::~Window()
{
}

bool Window::Init(int width, int height, std::string title)
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		return false;

	return true;
}

void Window::Shutdown()
{
	glfwTerminate();
}

void Window::Update()
{
	SwapBuffers();
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}
