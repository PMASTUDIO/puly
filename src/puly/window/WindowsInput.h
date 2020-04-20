#pragma once

#include "..//lowlevel/Input.h"

class Window;

namespace Puly {

	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(Window* window, int keyCode) override;

		virtual bool IsMouseButtonPressedImpl(Window* window, int button) override;

		virtual float GetMouseXImpl(Window* window) override;
		virtual float GetMouseYImpl(Window* window) override;
	};

}