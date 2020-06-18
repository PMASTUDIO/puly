#include "Window.h"

#include "..//lowlevel/Event.h"
#include "..//lowlevel/BaseEvents.h"

#include <GL/glew.h>

namespace Puly {

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

	glfwSetWindowUserPointer(m_Window, &m_Data);

	// Enable VSync
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		Puly::WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		Puly::MouseScrolledEvent event(xoffset, yoffset);
		data.EventCallback(event);
	});

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

}

