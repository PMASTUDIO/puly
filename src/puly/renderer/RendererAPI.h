#pragma once

#include <memory>
#include "VertexArray.h"

namespace Puly {

	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_Api; }

	private:
		static API s_Api;
	};

	
}