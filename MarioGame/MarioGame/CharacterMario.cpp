#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_moving_left = false;
	m_moving_right = false;
	m_renderer = renderer;
	m_position = start_position;
	m_facing_direction = FACING_RIGHT;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_frame_count = 1;
	m_last_tick = 0;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;
}

void CharacterMario::Render()
{

	SDL_Rect portion_of_sprite = { (m_frame_count * m_single_sprite_w), 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	WalkAnimation();

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			m_frame_count = 1;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			m_frame_count = 1;
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);
	AddWindowCollision();

}

void CharacterMario::WalkAnimation()
{
	if (IsJumping())
		m_frame_count = 0;

	else if (m_moving_left || m_moving_right)
	{
		m_current_frame_time += ((SDL_GetTicks() - m_last_tick) / 75);

		if (m_current_frame_time > FRAME_TIME)
		{
			m_frame_count++;
			m_current_frame_time = 0;
			m_last_tick = SDL_GetTicks();

			if (m_frame_count > 2)
			{
				m_frame_count = 1;
			}
		}
	}
	else
		m_frame_count = 1;
}