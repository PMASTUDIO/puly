#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"

#include "lowlevel/debugging/DebugDrawManager.h"
#include "lowlevel/debugging/ImGuiSystem.h"

#include "Game.h"

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
		std::unique_ptr<SubSystems> mSubSystems;

		Shader m_Shader;

		//std::unique_ptr<DebugDrawManager> debugDrawManager;

		Game demoGame;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);
	};
}
