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
#include <glm/glm.hpp>

namespace Puly {

	class SpriteRenderer : public Component {
	public:
		SpriteRenderer(const char* texturePath,
			const char* vertexShaderPath = "resources/shaders/textureVertexShader.glsl", 
			const char* fragmentShaderPath = "resources/shaders/textureFragmentShader.glsl",
			glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		);

		~SpriteRenderer();

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		void SaveInScene(std::string section, GameLevel& levelSave) override;

		static SpriteRenderer& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;

		std::string m_TexturePath;
		std::string m_VertexShaderPath;
		std::string m_FragmentShaderPath;

		glm::vec4 m_Color;

		void InitRenderData();
	};

}