#include "WindowsInput.h"
#include "Window.h"

#include <GLFW/glfw3.h>

#include <iostream>

Puly::Input* Puly::Input::s_Instance = new Puly::WindowsInput();

bool Puly::WindowsInput::IsKeyPressedImpl(Puly::Window* window, int keyCode)
{
	auto state = glfwGetKey(window->GetNativeWindow(), keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Puly::WindowsInput::IsMouseButtonPressedImpl(Puly::Window* window, int button)
{
	auto state = glfwGetMouseButton(window->GetNativeWindow(), button);
	return state == GLFW_PRESS;
}

float Puly::WindowsInput::GetMouseXImpl(Puly::Window* window)
{
	double xpos;
	glfwGetCursorPos(window->GetNativeWindow(), &xpos, nullptr);

	return (float)xpos;
}

float Puly::WindowsInput::GetMouseYImpl(Puly::Window* window)
{
	double ypos;
	glfwGetCursorPos(window->GetNativeWindow(), nullptr, &ypos);

	return (float)ypos;
}
