#pragma once
#include "window/Window.h"
#include "SubSystems.h"

#include "renderer/Shader.h"
#include "renderer/Buffer.h"

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

		unsigned int m_VertexArray;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		float mLastFrameTime;

		float GetDeltaTime(int targetFPS);
	};
}
