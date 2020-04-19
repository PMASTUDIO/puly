#include "Window.h"

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

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

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
