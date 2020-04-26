#pragma once

#include "..//renderer/RendererAPI.h"

namespace Puly {

	class OpengGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;

		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}