#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"
#include "platform/windows/FileOpenDialog.h"

#include "ecs/components/MoveComponent.h"

#include <imgui.h>

#include <glm/glm.hpp>

// Test colliding rectangles
#include "physics/Collision.h"

Puly::Game::Game(Window* window, unsigned int width, unsigned int height) : mWidth(width), mHeight(height), m_State(GAME_ACTIVE), mOwnerWindow(window)
, mainScene(*window)
{	
	//m_EntityManager.reset(new EntityManager(window));
}

Puly::Game::~Game()
{
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);

	mainScene.OnStart();
	mainScene.LoadSceneFromFile("resources/scenes/breakoutLevelTestWithBouncingBall.ini");
	/*Puly::GameObject& checkerboard(m_EntityManager->AddObject(1, "checkerboard"));
	checkerboard.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");*/
}

void Puly::Game::Update(Timestep dt)
{
	mainScene.OnUpdate(dt);
	//m_EntityManager->Update(dt);
}

void Puly::Game::Render()
{
	mainScene.Render();
	//m_EntityManager->Render();
}
