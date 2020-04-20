#pragma once

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class Window {
public:
	Window();
	~Window();

	bool Init(int width, int height, std::string title);
	void Shutdown();

	void Update();

	bool ShouldClose();

	GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window;

	void SwapBuffers();
};