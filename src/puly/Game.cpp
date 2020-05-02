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
	m_EntityManager.reset(new EntityManager(*window));
}

Puly::Game::~Game()
{
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);

	Puly::GameObject& checkerboard(m_EntityManager->AddObject(1, "checkerboard1"));
	checkerboard.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");
	checkerboard.AddComponent<Puly::ColliderComponent>(m_EntityManager.get());

	Puly::GameObject& checkerboard2(m_EntityManager->AddObject(1, "checkerboard2"));
	checkerboard2.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");
	checkerboard2.AddComponent<Puly::ColliderComponent>(m_EntityManager.get());

	checkerboard.m_Position.x += 2.0f;

	if (CheckRectCollision2D(checkerboard, checkerboard2)) {
		PL_LOG_INFO("Rectangles colliding");
	}
}

void Puly::Game::Update(Timestep dt)
{
	m_EntityManager->Update(dt);
}

void Puly::Game::Render()
{
	m_EntityManager->Render();
}
