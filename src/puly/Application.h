#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Texture.h"

#include "lowlevel/debugging/DebugDrawManager.h"
#include "lowlevel/debugging/ImGuiSystem.h"

#include "renderer/OrthographicCamera.h"
#include <glm/glm.hpp>

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

		//Shader m_Shader;

		std::shared_ptr<Shader> m_Shader, m_TextureShader;

		//std::unique_ptr<DebugDrawManager> debugDrawManager;

		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;
		std::shared_ptr<VertexArray> m_VAO;

		std::shared_ptr<Texture> m_Texture;

		Game demoGame;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);

		OrtographicCamera m_Camera;
	};
}
