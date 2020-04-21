#pragma once

namespace Puly {

	enum class RendererAPI {
		None = 0, OpenGL = 1
	};

	class Renderer {
	public:

		inline static RendererAPI GetAPI() { return s_RenderApi; }

	private:
		static RendererAPI s_RenderApi;
	};

}