#pragma once

#include <map>
#include "renderer/SpriteRenderer.h"

#include "objects/GameObject.h"

#include "./lowlevel/Timestep.h"

#include "ecs/EntityManager.h"
#include "ecs/Scene2D.h"
#include "ecs/components/Effects/ParticleEmitterComponent.h"

namespace Puly {
	
	enum GameState {
		GAME_ACTIVE,
		GAME_PAUSED,
		GAME_WIN
	};

	class Game {
	public:
		Game(Window* window, unsigned int width, unsigned int height);
		~Game();

		void Start();
		void Update(Timestep dt);

		void Render();

	public:
		GameState m_State;
		unsigned int mWidth, mHeight;

		//std::unique_ptr<EntityManager> m_EntityManager;
		Scene2D mainScene;

		std::vector<Puly::GameObject*> boxes;

		GameObject* m_Ball;
		GameObject* m_Paddle;
		GameObject* m_ParticleBallEmitter;

		ParticleProps particleBall;

		Window* mOwnerWindow;
	};

}