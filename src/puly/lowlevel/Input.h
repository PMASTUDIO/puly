#pragma once

namespace Puly {

	class Window;

	class Input {
	public:
		inline static bool IsKeyPressed(Puly::Window* window, int keyCode) { return s_Instance->IsKeyPressedImpl(window, keyCode); }

		inline static bool IsMouseButtonPressed(Puly::Window* window, int button) { return s_Instance->IsMouseButtonPressedImpl(window, button); }
	
		inline static float GetMouseX(Puly::Window* window) { return s_Instance->GetMouseXImpl(window); }
		inline static float GetMouseY(Puly::Window* window) { return s_Instance->GetMouseYImpl(window); }

	protected:
		virtual bool IsKeyPressedImpl(Puly::Window* window, int keyCode) = 0;
		
		virtual bool IsMouseButtonPressedImpl(Puly::Window* window, int button) = 0;

		virtual float GetMouseXImpl(Puly::Window* window) = 0;
		virtual float GetMouseYImpl(Puly::Window* window) = 0;
	private:
		static Input* s_Instance;
	};
}