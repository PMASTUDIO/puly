#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"
#include "platform/windows/FileOpenDialog.h"

#include <imgui.h>

#include <glm/glm.hpp>

// Test colliding rectangles
#include "physics/Collision.h"
#include <string>

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

	//m_Ball = mainScene.GetEntityManager()->GetObjectByDebugName("ball");
	//m_Paddle = mainScene.GetEntityManager()->GetObjectByDebugName("paddle");

	//// Breakout demo
	//float blockX = -1.75f;
	//float blockY =  0.7f;
	//int indexBrick = 0;
	//for (int j = 0; j < 3; j++) {
	//	for (int i = 0; i < 13; i++) {
	//		std::string objName = "brick" + std::to_string(indexBrick);
	//		Puly::GameObject& brick(mainScene.GetEntityManager()->AddObject(2, objName.c_str(), true));

	//		brick.AddComponent<Puly::SpriteRenderer>("resources/textures/brick.png");
	//		brick.AddComponent<Puly::ColliderComponent>(mainScene.GetEntityManager().get());
	//		brick.m_Scale = glm::vec3(0.3f);
	//		brick.m_Position.x = blockX;
	//		brick.m_Position.y = blockY;
	//		blockX += 0.3f;
	//		indexBrick++;
	//		boxes.push_back(&brick);
	//	}
	//	blockX = -1.75f;
	//	blockY -= 0.3f;
	//}
}

void Puly::Game::Update(Timestep dt)
{
	mainScene.OnUpdate(dt);
}

void Puly::Game::Render()
{
	mainScene.Render();
	//m_EntityManager->Render();
}
