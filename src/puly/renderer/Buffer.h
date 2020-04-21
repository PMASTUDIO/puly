#pragma once

#include <stdint.h>
#include <string>

#include <GL/glew.h>

#include "..//lowlevel/debugging/Log.h"

namespace Puly {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static GLenum ShaderDataTypeToOpenGl(ShaderDataType type) {
		switch (type)
		{
		case Puly::ShaderDataType::Float:
			return GL_FLOAT;
		case Puly::ShaderDataType::Float2:
			return GL_FLOAT;
		case Puly::ShaderDataType::Float3:
			return GL_FLOAT;
		case Puly::ShaderDataType::Float4:
			return GL_FLOAT;
		case Puly::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Puly::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Puly::ShaderDataType::Int:
			return GL_INT;
		case Puly::ShaderDataType::Int2:
			return GL_INT;
		case Puly::ShaderDataType::Int3:
			return GL_INT;
		case Puly::ShaderDataType::Int4:
			return GL_INT;
		case Puly::ShaderDataType::Bool:
			return GL_BOOL;
		}
	}

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Puly::ShaderDataType::None:
			break;
		case Puly::ShaderDataType::Float:
			return 4;
		case Puly::ShaderDataType::Float2:
			return 4 * 2;
		case Puly::ShaderDataType::Float3:
			return 4 * 3;
		case Puly::ShaderDataType::Float4:
			return 4 * 4;
		case Puly::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case Puly::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case Puly::ShaderDataType::Int:
			return 4;
		case Puly::ShaderDataType::Int2:
			return 4 * 2;
		case Puly::ShaderDataType::Int3:
			return 4 * 3;
		case Puly::ShaderDataType::Int4:
			return 4 * 4;
		case Puly::ShaderDataType::Bool:
			return 1;
		}

		PL_LOG_ERROR("Unknon data type!");
		return 0;
	};

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement(){}

		BufferElement(ShaderDataType type, const std::string& name) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(false){
		}

		uint32_t GetComponentCount() const {
			switch (Type) {
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3: return 3 * 3;
				case ShaderDataType::Mat4: return 4 * 4;
				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;
				case ShaderDataType::Bool: return 1;
				case ShaderDataType::None: return 0;
			}

			PL_LOG_ERROR("Unknown data type!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& element) : m_Elements(element) {
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	private:
		std::vector<BufferElement> m_Elements;

		uint32_t m_Stride = 0;

		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}