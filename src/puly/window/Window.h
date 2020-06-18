#pragma once

#include <string>

#include "..//lowlevel/Event.h"
#include <functional>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

namespace Puly {
	class Window {
	public:
		using EventCallbackFn = std::function<void(Puly::Event&)>;

		Window();
		~Window();

		bool Init(int width, int height, std::string title);
		void Shutdown();

		void Update();

		bool ShouldClose();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		GLFWwindow* GetNativeWindow() const { return m_Window; }

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		void SwapBuffers();
	};
}