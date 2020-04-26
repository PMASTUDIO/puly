#pragma once

#include "RendererAPI.h"

namespace Puly {

	class RenderCommand {
	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(float r, float g, float b, float a) {
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}