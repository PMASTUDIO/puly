#include "SpriteRenderer.h"

#include "..//lowlevel/ResourceManager.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Puly {

	SpriteRenderer::SpriteRenderer(std::shared_ptr<Shader>& Shader, const char* texturePath)
	{
		this->m_Shader = Shader;
		InitRenderData();

		m_Texture = Puly::Texture2D::Create(texturePath);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		
	}

	void SpriteRenderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
	{
		m_Shader->Bind();
		m_Shader->UploadUniform1i("u_Texture", 0);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model = glm::scale(model, glm::vec3(size, 1.0f));

		m_Texture->Bind();

		Renderer::Submit(m_VAO, m_Shader, model);
	}

	void SpriteRenderer::InitRenderData()
	{
		m_VAO.reset(VertexArray::Create());

		float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f
		};

		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
		m_VAO->SetIndexBuffer(m_IBO);

		auto textureShaderTexts = ResourceManager::GetShaderText("resources/shaders/textureVertexShader.glsl", "resources/shaders/textureFragmentShader.glsl");
		m_Shader->Compile(std::get<0>(textureShaderTexts), std::get<1>(textureShaderTexts));
	}

}
