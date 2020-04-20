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

		Shader m_Shader;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);
	};
}
