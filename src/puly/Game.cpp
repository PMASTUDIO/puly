#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "ecs/components/MoveComponent.h"

#include <imgui.h>

#include <glm/glm.hpp>

// Test colliding rectangles
#include "physics/Collision.h"

Puly::Game::Game(Window* window, unsigned int width, unsigned int height) : mWidth(width), mHeight(height), m_State(GAME_ACTIVE), mOwnerWindow(window)
{	
	m_EntityManager.reset(new EntityManager(window));
}

Puly::Game::~Game()
{
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);

	Puly::GameObject& checkerboard(m_EntityManager->AddObject(1, "checkerboard"));
	checkerboard.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");

	checkerboard.m_Position.x += 2.0f;
}

void Puly::Game::Update(Timestep dt)
{
	m_EntityManager->Update(dt);
}

void Puly::Game::Render()
{
	m_EntityManager->Render();
}
