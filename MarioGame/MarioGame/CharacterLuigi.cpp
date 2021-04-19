#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_moving_left = false;
	m_moving_right = false;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_LEFT;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

CharacterLuigi::~CharacterLuigi()
{
	m_renderer = nullptr;
}

void CharacterLuigi::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE, 0.0f);
	if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump)
			{
				Jump();
			}
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);

	//stops from exiting screen to left
	if (GetPosition().y < 300 && GetPosition().y > 100 && GetPosition().x < 0)
	{
		SetPosition(Vector2D(1, GetPosition().y));
	}

	//stops from exiting screen to right
	if (GetPosition().y < 300 && GetPosition().y > 100 && (GetPosition().x + (m_texture->GetWidth() / 2) > SCREEN_WIDTH - 10))
	{
		SetPosition(Vector2D(SCREEN_WIDTH - m_texture->GetWidth(), GetPosition().y));
	}

}

