#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"
#include "platform/windows/FileOpenDialog.h"

#include "ecs/components/MoveComponent.h"

#include <imgui.h>

#include <glm/glm.hpp>

// Test colliding rectangles
#include "physics/Collision.h"
#include <string>
#include "ecs/components/Breakout/BallBreakoutComponent.h"

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
	mainScene.LoadSceneFromFile("resources/scenes/breakoutLevelTestWithPaddleCollision3.ini");

	// Breakout demo
	float blockX = -1.75f;
	float blockY =  0.7f;
	int indexBrick = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 13; i++) {
			std::string objName = "brick" + std::to_string(indexBrick);
			Puly::GameObject& brick(mainScene.GetEntityManager()->AddObject(2, objName.c_str()));

			brick.AddComponent<Puly::SpriteRenderer>("resources/textures/brick.png");
			brick.AddComponent<Puly::ColliderComponent>();
			brick.m_Scale = glm::vec3(0.3f);
			brick.m_Position.x = blockX;
			brick.m_Position.y = blockY;
			blockX += 0.3f;
			indexBrick++;
			boxes.push_back(&brick);
		}
		blockX = -1.75f;
		blockY -= 0.3f;
	}
}

void Puly::Game::Update(Timestep dt)
{
	mainScene.OnUpdate(dt);

	GameObject* ball = mainScene.GetEntityManager()->GetObjectByDebugName("ball");
	BallBreakoutComponent* comp = ball->GetComponent<BallBreakoutComponent>();
	glm::vec2 vel = comp->GetSpeed();

	// Check collision with paddle
	if (mainScene.GetEntityManager()->CheckEntityCollider(*ball).compare("paddle") == 0) {
		comp->SetSpeed(glm::vec2(vel.x, -vel.y));
		PL_LOG_INFO("Collided with paddle!");
	}

	// Check collision with brick
	for (auto& box : boxes) {
		const char* name = box->m_DebugName.c_str();
		if (mainScene.GetEntityManager()->CheckEntityCollider(*ball).compare(box->m_DebugName.c_str()) == 0) {
			box->Destroy();
			comp->SetSpeed(glm::vec2(vel.x, -vel.y));
			std::remove(boxes.begin(), boxes.end(), box);
		}
	}

}

void Puly::Game::Render()
{
	mainScene.Render();
	//m_EntityManager->Render();
}
