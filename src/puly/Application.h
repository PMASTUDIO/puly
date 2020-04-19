#pragma once
#include "window/Window.h"
#include "SubSystems.h"

namespace Puly {
	class Application {
	public:
		Application();
		~Application();

		bool Init();
		bool Shutdown();

		void Run();

	private:
		Window mWindow;
		SubSystems mSubSystems;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);
	};
}
