#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetBackground("Images/Menu.png");
}

GameScreenMenu::~GameScreenMenu()
{
	m_background_texture = nullptr;
}

void GameScreenMenu::Render()
{

}
void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}