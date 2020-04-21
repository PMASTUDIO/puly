#include "Game.h"

#include "lowlevel/debugging/Log.h"

Puly::Game::Game(unsigned int width, unsigned int height) : mWidth(width), mHeight(height), m_State(GAME_ACTIVE)
{
}

Puly::Game::~Game()
{
	PL_LOG_SUCCESS("Game destroyed!");
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);
}

void Puly::Game::Update(Timestep dt)
{
}

void Puly::Game::Render()
{
}
