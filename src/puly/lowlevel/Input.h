#pragma once

class Window;

namespace Puly {
	class Input {
	public:
		inline static bool IsKeyPressed(Window* window, int keyCode) { return s_Instance->IsKeyPressedImpl(window, keyCode); }

		inline static bool IsMouseButtonPressed(Window* window, int button) { return s_Instance->IsMouseButtonPressedImpl(window, button); }
	
		inline static float GetMouseX(Window* window) { return s_Instance->GetMouseXImpl(window); }
		inline static float GetMouseY(Window* window) { return s_Instance->GetMouseYImpl(window); }

	protected:
		virtual bool IsKeyPressedImpl(Window* window, int keyCode) = 0;
		
		virtual bool IsMouseButtonPressedImpl(Window* window, int button) = 0;

		virtual float GetMouseXImpl(Window* window) = 0;
		virtual float GetMouseYImpl(Window* window) = 0;
	private:
		static Input* s_Instance;
	};
}