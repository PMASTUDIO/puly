#include "SpriteRenderer.h"

#include "..//lowlevel/ResourceManager.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

#include "..//objects/GameObject.h"
#include "..//imgui/imgui.h"

namespace Puly {

	SpriteRenderer::SpriteRenderer(const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath) : m_TexturePath(texturePath), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
	{
		m_Shader.reset(new Shader());

		auto shaderTexts = ResourceManager::GetShaderText(vertexShaderPath, fragmentShaderPath);
		m_Shader->Compile(std::get<0>(shaderTexts), std::get<1>(shaderTexts));

		InitRenderData();

		m_Texture = Puly::Texture2D::Create(texturePath);
	}

	void SpriteRenderer::Init()
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
		
	}

	void SpriteRenderer::Update(float deltaTime)
	{
	}

	void SpriteRenderer::Render()
	{
		glm::vec2 position = glm::vec2(m_Owner->m_Position.x, m_Owner->m_Position.y);

		glm::vec2 size = glm::vec2(m_Owner->m_Scale.x, m_Owner->m_Scale.y);
		float rotate = glm::radians(m_Owner->m_Rotation);

		m_Shader->Bind();
		m_Shader->UploadUniform1i("u_Texture", 0);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model = glm::scale(model, glm::vec3(size, 1.0f));

		m_Texture->Bind();

		Renderer::Submit(m_VAO, m_Shader, model);
	}

	void SpriteRenderer::DebugGUI()
	{
		ImGui::Text("Sprite Component");
	}

	void SpriteRenderer::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "texturePath", m_TexturePath.c_str());
		levelSave.configurator.SetValue(section.c_str(), "vertexShaderPath", m_VertexShaderPath.c_str());
		levelSave.configurator.SetValue(section.c_str(), "fragmentShaderPath", m_FragmentShaderPath.c_str());
	}

	Puly::SpriteRenderer& SpriteRenderer::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		const char* texPath = config.GetValue(section.c_str(), "texturePath");
		const char* vertexShaderPath = config.GetValue(section.c_str(), "vertexShaderPath");
		const char* fragmentShaderPath = config.GetValue(section.c_str(), "fragmentShaderPath");

		SpriteRenderer& newComponent = go.AddComponent<SpriteRenderer>(texPath, vertexShaderPath, fragmentShaderPath);
		return newComponent;
	}

	void SpriteRenderer::InitRenderData()
	{
		m_VAO = Renderer::Draw2DQuad();
	}

}
