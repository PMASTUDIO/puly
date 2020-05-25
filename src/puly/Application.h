#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include <vector>

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Texture.h"

#include "lowlevel/debugging/ImGuiSystem.h"

#include "renderer/SpriteRenderer.h"

#include "renderer/OrthographicCameraController.h"
#include <glm/glm.hpp>

#include "ecs/EntityManager.h"

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

		std::shared_ptr<Shader> m_Shader;

		std::unique_ptr<OrthographicCamera2DController> m_CameraController;

		std::unique_ptr<Game> demoGame;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);

		float gameMinimized = false;
	};
}
