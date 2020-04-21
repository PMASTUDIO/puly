#pragma once

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

	private:
		GameState m_State;
		unsigned int mWidth, mHeight;
	};

}