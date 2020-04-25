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
	std::shared_ptr<SpriteRenderer> checkerboard;
	checkerboard.reset(new SpriteRenderer("resources/textures/checkerboard.png"));

	std::shared_ptr<SpriteRenderer> bird;
	bird.reset(new SpriteRenderer("resources/textures/bird.png"));

	v_SpriteRenderers["Bird"] = bird;
	v_SpriteRenderers["Checkerboard"] = checkerboard;
}

void Puly::Game::Update(Timestep dt)
{
	
}

void Puly::Game::Render()
{
	float i = 0.0f;

	for (auto& element : v_SpriteRenderers) {
		element.second->DrawSprite(glm::vec2(i, 0.0f), glm::vec2(1.0f), 0.0f, glm::vec3(1.0f));

		i += 1.0f;
	}
}
