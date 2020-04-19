#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();
	~Window();

	bool Init(int width, int height, std::string title);
	void Shutdown();

	void Update();

	bool ShouldClose();

private:
	GLFWwindow* m_Window;

	void SwapBuffers();
};