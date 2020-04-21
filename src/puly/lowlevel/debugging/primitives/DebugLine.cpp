#include "DebugLine.h"
#include "../..//ResourceManager.h"

Puly::DebugLine::DebugLine(const Point& fromPosition, const Point& toPosition) : lineVertices{ fromPosition.x, fromPosition.y, fromPosition.z, toPosition.x, toPosition.y, toPosition.z }
{
	Setup();
}

Puly::DebugLine::~DebugLine()
{
}

void Puly::DebugLine::DrawLine()
{
	m_VertexArray->Bind();

	m_Shader.Bind();
	glDrawArrays(GL_LINES, 0, 2);
	m_Shader.Unbind();

}

void Puly::DebugLine::Setup()
{
	m_VertexBuffer.reset(VertexBuffer::Create(lineVertices, sizeof(lineVertices)));
	m_VertexArray.reset(VertexArray::Create());

	BufferLayout layout{
		{ ShaderDataType::Float3, "a_Position" }
	};

	m_VertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t indices[2] = { 0, 1 };
	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	auto shaderFiles = ResourceManager::GetShaderText("resources/shaders/debugVertexShader.glsl", "resources/shaders/debugFragmentShader.glsl");
	m_Shader.Compile(std::get<0>(shaderFiles), std::get<1>(shaderFiles));
}
