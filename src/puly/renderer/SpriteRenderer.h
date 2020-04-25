#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

#include "Buffer.h"
#include "VertexArray.h"
#include "Texture.h"

namespace Puly {

	class SpriteRenderer {
	public:
		SpriteRenderer(const char* texturePath,
			const char* vertexShaderPath = "resources/shaders/textureVertexShader.glsl", 
			const char* fragmentShaderPath = "resources/shaders/textureFragmentShader.glsl"
			);

		~SpriteRenderer();

		void DrawSprite(
			glm::vec2 position, 
			glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
			glm::vec3 color = glm::vec3(1.0f)
		);

	private:
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;
		std::shared_ptr<VertexArray> m_VAO;

		std::shared_ptr<Texture> m_Texture;

		void InitRenderData();
	};

}