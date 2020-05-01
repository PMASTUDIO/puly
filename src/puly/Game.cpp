#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "ecs/components/MoveComponent.h"

#include <imgui.h>

#include <glm/glm.hpp>

Puly::Game::Game(Window* window, unsigned int width, unsigned int height) : mWidth(width), mHeight(height), m_State(GAME_ACTIVE), mOwnerWindow(window)
{
	m_EntityManager.reset(new EntityManager());
}

Puly::Game::~Game()
{
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);

	Puly::GameObject& checkerboard(m_EntityManager->AddObject(mOwnerWindow, "checkerboard"));
	checkerboard.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");
}

void Puly::Game::Update(Timestep dt)
{
	m_EntityManager->Update(dt);
}

void Puly::Game::Render()
{
	m_EntityManager->Render();
}
