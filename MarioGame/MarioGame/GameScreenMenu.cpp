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
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}
void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}