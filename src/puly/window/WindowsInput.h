#pragma once

#include "..//lowlevel/Input.h"

class Window;

namespace Puly {

	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(Puly::Window* window, int keyCode) override;

		virtual bool IsMouseButtonPressedImpl(Puly::Window* window, int button) override;

		virtual float GetMouseXImpl(Puly::Window* window) override;
		virtual float GetMouseYImpl(Puly::Window* window) override;
	};

}