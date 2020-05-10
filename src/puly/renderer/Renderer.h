#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include <glm/glm.hpp>

#include "Texture.h"

namespace Puly {

	class Renderer {
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrtographicCamera& camera);
		static void EndScene();

		static void Draw2DQuad(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::mat4& transform = glm::mat4(1.0f));
		static void Draw2DQuad(const std::shared_ptr<Shader>& shader, glm::vec4 color, const glm::mat4& transform = glm::mat4(1.0f));
		
		static void Draw2DLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color);

		//static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Shutdown();

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}