#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include "renderer/Shader.h"

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

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);
	};
}
