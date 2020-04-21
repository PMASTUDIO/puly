#pragma once

#include <memory>
#include <GL/glew.h>

#include "../../../renderer/Buffer.h"

#include "../../../renderer/VertexArray.h"
#include "../../../renderer/Buffer.h"
#include "../../../renderer/Shader.h"

#include "Point.h"



namespace Puly {
	class DebugLine {
	public:
		DebugLine(){}
		DebugLine(const Point& fromPosition, const Point& toPosition);
		~DebugLine();

		void DrawLine();

	private:
		 GLfloat lineVertices[6];

		 void Setup();

		 Shader m_Shader;

		 std::shared_ptr<VertexBuffer> m_VertexBuffer;
		 std::shared_ptr<IndexBuffer> m_IndexBuffer;
		 std::shared_ptr<VertexArray> m_VertexArray;
	};
}