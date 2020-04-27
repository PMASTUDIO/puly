#include "Game.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include <imgui.h>

#include <glm/glm.hpp>

Puly::Game::Game(unsigned int width, unsigned int height) : mWidth(width), mHeight(height), m_State(GAME_ACTIVE)
{
}

Puly::Game::~Game()
{
}

void Puly::Game::Start()
{
	PL_LOG_SUCCESS("Game initialized! Width: {}, Height: {}", mWidth, mHeight);

	// Texture Shader setup
	std::shared_ptr<Shader> shader;
	shader.reset(new Shader());

	v_Shaders.push_back(shader);
	
	auto textureShaderTexts = ResourceManager::GetShaderText("resources/shaders/textureVertexShader.glsl", "resources/shaders/textureFragmentShader.glsl");
	shader->Compile(std::get<0>(textureShaderTexts), std::get<1>(textureShaderTexts));


	// Texture Renderer setups
	//std::shared_ptr<GameObject> checkerboard;
	//checkerboard.reset(new GameObject(glm::vec3(0.0f), "resources/textures/checkerboard.png"));

	//std::shared_ptr<SpriteRenderer> bird;
	//bird.reset(new SpriteRenderer("resources/textures/bird.png"));

	//v_Objects["Checkerboard"] = checkerboard;
	//v_SpriteRenderers["Checkerboard"] = checkerboard;
}

void Puly::Game::Update(Timestep dt)
{
}

void Puly::Game::Render()
{
	
}
