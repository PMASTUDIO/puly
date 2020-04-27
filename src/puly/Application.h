#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Texture.h"

#include "lowlevel/debugging/DebugDrawManager.h"
#include "lowlevel/debugging/ImGuiSystem.h"

#include "renderer/SpriteRenderer.h"

#include "renderer/OrthographicCameraController.h"
#include <glm/glm.hpp>

#include "Game.h"

namespace Puly {
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class Application {
	public:
		Application();
		~Application();

		bool Init();
		bool Shutdown();

		void OnEvent(Event& evt);

		void Run();

	private:
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Window mWindow;
		std::unique_ptr<SubSystems> mSubSystems;

		//Shader m_Shader;

		OrthographicCamera2DController m_CameraController;

		Game demoGame;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);

		float gameMinimized = false;
	};
}
