#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace Puly {

	class Renderer {
	public:
		static void Init();

		static void BeginScene(OrtographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}