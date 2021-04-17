#include "GameScreen.h"
#include <SDL_image.h>
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

bool GameScreen::SetBackground(string path)
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile(path))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}



void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}