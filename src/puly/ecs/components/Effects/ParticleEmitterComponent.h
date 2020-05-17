#pragma once

#include "../../Component.h"
#include <glm/glm.hpp>
#include "../../../renderer/Shader.h"

namespace Puly {

	struct ParticleProps {
		glm::vec2 position;
		glm::vec2 velocity, velocityVariation;
		glm::vec4 colorBegin, colorEnd;
		float sizeBegin, sizeEnd, sizeVariation;
		float lifeTime = 1.0f;
	};

	class ParticleEmitterComponent : public Component {
	public:

		ParticleEmitterComponent(
			const char* vertexShaderPath = "resources/shaders/colorVertexShader.glsl",
			const char* fragmentShaderPath = "resources/shaders/colorFragmentShader.glsl"
		);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		void Emit(const ParticleProps& particleProps);

		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static ParticleEmitterComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		struct Particle {
			glm::vec2 position;
			glm::vec2 velocity;
			glm::vec4 colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd;

			float lifeTime = 1.0f;
			float lifeRemaining = 0.0f;

			bool Active = false;
		};

		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 999;

		std::shared_ptr<Shader> m_Shader;

		std::string m_VertexShaderPath;
		std::string m_FragmentShaderPath;

		#ifdef PL_DEBUG
		ParticleProps particleDefault;
		#endif
	};

}