#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_frame_count = 0;
	m_last_tick = 0;
}
CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Render()
{
	SDL_Rect portion_of_sprite = { (m_frame_count * m_single_sprite_w), 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	
}

void CharacterCoin::Update()
{
	m_current_frame_time += ((SDL_GetTicks() - m_last_tick) / 100);

	if (m_current_frame_time > FRAME_TIME)
	{
		m_frame_count++;
		m_current_frame_time = 0;
		m_last_tick = SDL_GetTicks();

		if (m_frame_count >= 2)
		{
			m_frame_count = 0;
			
		}
	}

}