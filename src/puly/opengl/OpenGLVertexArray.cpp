#include "OpenGLVertexArray.h"

Puly::OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererId);
}

void Puly::OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererId);
}

void Puly::OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void Puly::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererId);
	vertexBuffer->Bind();

	uint32_t index = 0;

	const auto& layout = vertexBuffer->GetLayout();

	for (const auto& element : layout) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGl(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset
		);

		index++;
	}

	m_VertexBuffers.push_back(vertexBuffer);

}

void Puly::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererId);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}
