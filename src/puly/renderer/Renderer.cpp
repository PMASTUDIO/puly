#include "Renderer.h"

namespace Puly {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrtographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		
	}

	std::shared_ptr<VertexArray> Renderer::Draw2DQuad()
	{
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;
		std::shared_ptr<VertexArray> VAO;

		VAO.reset(VertexArray::Create());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f
		};

		VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};
		VBO->SetLayout(layout);
		VAO->AddVertexBuffer(VBO);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
		VAO->SetIndexBuffer(IBO);

		return VAO;
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

		shader->Unbind();
		vertexArray->Unbind();
	}
}