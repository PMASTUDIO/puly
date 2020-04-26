#pragma once

#include <map>
#include "renderer/SpriteRenderer.h"

#include "objects/GameObject.h"

#include "./lowlevel/Timestep.h"

namespace Puly {
	
	enum GameState {
		GAME_ACTIVE,
		GAME_PAUSED,
		GAME_WIN
	};

	class Game {
	public:
		Game(unsigned int width, unsigned int height);
		~Game();

		void Start();
		void Update(Timestep dt);

		void Render();

	public:
		GameState m_State;
		unsigned int mWidth, mHeight;

		std::map<std::string, std::shared_ptr<GameObject>> v_Objects;
		std::vector<std::shared_ptr<Shader>> v_Shaders;
	};

}