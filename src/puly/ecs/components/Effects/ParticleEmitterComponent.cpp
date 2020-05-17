#include "ParticleEmitterComponent.h"

#include "..//../../lowlevel/Input.h"
#include "..//../../lowlevel/KeyCodes.h"
#include "..//../../lowlevel/debugging/Log.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "..//../../objects/GameObject.h"
#include "../../../lowlevel/ResourceManager.h"
#include "../../../renderer/Renderer.h"
#include "../../../lowlevel/Random.h"
#include "../puly/lowlevel/MouseButtonCodes.h"

bool continuousTesting = false;

namespace Puly {
	ParticleEmitterComponent::ParticleEmitterComponent(const char* vertexShaderPath, const char* fragmentShaderPath) : m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
	{
		m_Shader.reset(new Shader);
		m_ParticlePool.resize(1000);

		#ifdef PL_DEBUG
		particleDefault.colorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
		particleDefault.colorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		particleDefault.sizeBegin = 2.0f, particleDefault.sizeVariation = 0.3f, particleDefault.sizeEnd = 0.0f;
		particleDefault.lifeTime = 1.0f;
		particleDefault.velocity = { 0.0f, 0.0f };
		particleDefault.velocityVariation = { 3.0f, 1.0f };
		particleDefault.position = { 0.0f, 0.0f };
		#endif
	}
	void ParticleEmitterComponent::Init()
	{
		m_Shader = ResourceManager::GetShader(m_VertexShaderPath, m_FragmentShaderPath);
	}
	void ParticleEmitterComponent::Update(float deltaTime)
	{
		for (auto& particle : m_ParticlePool) {
			if (!particle.Active)
				continue;

			if (particle.lifeRemaining <= 0.0f) {
				particle.Active = false;
				continue;
			}

			particle.lifeRemaining -= deltaTime;
			particle.position += particle.velocity * deltaTime;
			particle.rotation += 0.01f * deltaTime;
		}
	}
	void ParticleEmitterComponent::Render()
	{
		for (auto& particle : m_ParticlePool) {
			//if (!particle.Active)
			//	continue;

			//// Fade away particles
			float life = particle.lifeRemaining / particle.lifeTime;
			glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
			color.a = color.a * life;

			float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);

			glm::mat4 model = glm::translate(glm::mat4(1.0f), { particle.position.x, particle.position.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), particle.rotation, { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size, size, 1.0f });

			Renderer::Draw2DQuad(m_Shader, color, model);
		}

		
	}

	void ParticleEmitterComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Particle Component")) {


			if (ImGui::Button("Emit 1")) {
				Emit(particleDefault);
			}

			ImGui::Checkbox("Continuous testing", &continuousTesting);

			if (continuousTesting) {
				for(int i = 0; i < 5; i++)
					Emit(particleDefault);
			}

			ImGui::BeginGroup();
			ImGui::SliderFloat2("Velocity", glm::value_ptr(particleDefault.velocity), 0.0f, 100.0f);
			ImGui::SliderFloat2("Velocity Randomness", glm::value_ptr(particleDefault.velocityVariation), 0.0f, 100.0f);
			ImGui::EndGroup();

			ImGui::BeginGroup();
			ImGui::ColorEdit4("Birth Color", glm::value_ptr(particleDefault.colorBegin));
			ImGui::ColorEdit4("Death Color", glm::value_ptr(particleDefault.colorEnd));
			ImGui::EndGroup();

			ImGui::BeginGroup();
			ImGui::DragFloat("Initial Size", &particleDefault.sizeBegin, 0.1f, 0.0f, 1000.0f);
			ImGui::DragFloat("Ending Size", &particleDefault.sizeEnd, 0.1f, 0.0f, 1000.0f);
			ImGui::DragFloat("Size Randomness", &particleDefault.sizeVariation, 0.1f, 0.0f, 1000.0f);
			ImGui::EndGroup();

			ImGui::DragFloat("Life Time", &particleDefault.lifeTime, 0.1f, 0.0f, 1000.0f);

			if (ImGui::Button("Delete")) {
				m_Owner->RemoveComponent<ParticleEmitterComponent>();
			}

			ImGui::TreePop();
		}
	}

	void ParticleEmitterComponent::Emit(const ParticleProps& particleProps)
	{
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.position = particleProps.position;
		particle.rotation = Random::GetFloat() * 2.0f * glm::pi<float>();

		// Velocity
		particle.velocity = particleProps.velocity;
		particle.velocity.x += particleProps.velocityVariation.x * (Random::GetFloat() - 0.5f);
		particle.velocity.y += particleProps.velocityVariation.y * (Random::GetFloat() - 0.5f);

		// Color
		particle.colorBegin = particleProps.colorBegin;
		particle.colorEnd = particleProps.colorEnd;

		// Lifetime
		particle.lifeTime = particleProps.lifeTime;
		particle.lifeRemaining = particleProps.lifeTime;

		// Size
		particle.sizeBegin = particleProps.sizeBegin * particleProps.sizeVariation * (Random::GetFloat() - 0.5f);
		particle.sizeEnd = particleProps.sizeEnd;

		m_PoolIndex -= m_PoolIndex % m_ParticlePool.size();
	}

	void ParticleEmitterComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		/*levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "positionX", std::to_string(m_Color.r).c_str());
		levelSave.configurator.SetValue(section.c_str(), "positionY", std::to_string(m_Color.r).c_str());*/
	}

	ParticleEmitterComponent& ParticleEmitterComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		/*float r = atof(config.GetValue(section.c_str(), "colorR"));
		float g = atof(config.GetValue(section.c_str(), "colorG"));
		float b = atof(config.GetValue(section.c_str(), "colorB"));
		float a = atof(config.GetValue(section.c_str(), "colorA"));*/

		ParticleEmitterComponent& newComponent = go.AddComponent<ParticleEmitterComponent>();

		return newComponent;
	}

}
