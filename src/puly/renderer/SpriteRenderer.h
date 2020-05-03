#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

#include "Buffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include "../ecs/Component.h"

namespace Puly {

	class SpriteRenderer : public Component {
	public:
		SpriteRenderer(const char* texturePath,
			const char* vertexShaderPath = "resources/shaders/textureVertexShader.glsl", 
			const char* fragmentShaderPath = "resources/shaders/textureFragmentShader.glsl"
		);

		~SpriteRenderer();

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;


		void SaveInScene(std::string section, GameLevel& levelSave) override;

	private:
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_VAO;

		std::shared_ptr<Texture> m_Texture;

		std::string m_TexturePath;
		std::string m_VertexShaderPath;
		std::string m_FragmentShaderPath;

		void InitRenderData();
	};

}