#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../lowlevel/ResourceManager.h"

namespace Puly {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	struct Render2DStorage {
		std::shared_ptr<VertexArray> VAO;
	};

	static Render2DStorage* s_Data;

	void Renderer::Init()
	{
		RenderCommand::Init();

		s_Data = new Render2DStorage();

		s_Data->VAO.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		float vertices[5 * 4] = {
			 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
			 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			 0.0f,  1.0f, 0.0f, 1.0f, 0.0f
		};

		VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};
		VBO->SetLayout(layout);
		s_Data->VAO->AddVertexBuffer(VBO);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
		s_Data->VAO->SetIndexBuffer(IBO);
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

	void Renderer::Draw2DQuad(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniform1i("u_Texture", 0);
		shader->UploadUniformFloat4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		texture->Bind();

		s_Data->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->VAO);

		//shader->Unbind();
		//s_Data->VAO->Unbind();
	}

	void Renderer::Draw2DQuad(const std::shared_ptr<Shader>& shader, glm::vec4 color, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformFloat4("u_Color", color.r, color.g, color.b, color.a);
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		s_Data->VAO->Bind();
		RenderCommand::DrawIndexed(s_Data->VAO);
	}

	void Renderer::Draw2DLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color)
	{
		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;
		std::shared_ptr<Shader> shader;


		shader = ResourceManager::GetShader("resources/shaders/lineVertexShader.glsl", "resources/shaders/lineFragmentShader.glsl");

		float vertices[3 * 3] = {
			p0.x, p0.y, p0.z,
			p1.x, p1.y, p1.z,
		};

		VAO.reset(VertexArray::Create());

		VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
		};
		VBO->SetLayout(layout);
		VAO->AddVertexBuffer(VBO);

		uint32_t indices[2] = { 0, 1 };
		IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
		VAO->SetIndexBuffer(IBO);

		shader->Bind();
		shader->UploadUniformFloat4("u_Color", color.r, color.g, color.b, color.a);
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));

		VAO->Bind();
		RenderCommand::DrawIndexedLine();
	}

	//void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	//{
	//	/*shader->Bind();
	//	shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
	//	shader->UploadUniformMat4("u_Transform", transform);*/

	//	/*vertexArray->Bind();
	//	RenderCommand::DrawIndexed(vertexArray);*/

	//	/*shader->Unbind();
	//	vertexArray->Unbind();*/
	//}
	void Renderer::Shutdown()
	{
		delete s_Data;
	}
}