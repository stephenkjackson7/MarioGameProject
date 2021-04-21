#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_frame_count = 1;
	m_last_tick = 0;

}
CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
	}
	else
		m_facing_direction = FACING_RIGHT;

	m_injured = false;
	Jump();
}

void CharacterKoopa::SetDirection(FACING direction)
{
	m_facing_direction = direction;
}

void CharacterKoopa::Render()
{
	//if injured move the left position to be the left position of the second image on sprite sheet
	if (m_injured)
		m_frame_count = 0;

	//get the portion of the sprite sheet you want to draw
	//							xPos, yPos, width of sprite, height of sprite
	SDL_Rect portion_of_sprite = { (m_frame_count * m_single_sprite_w), 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{

if (!m_injured)
{
	Character::Update(deltaTime, e);

	m_current_frame_time += ((SDL_GetTicks() - m_last_tick) / 125);

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



		//if koopa tries walking off-screen, turns around
		if (GetPosition().y < 300 && GetPosition().y > 75 && GetPosition().x < 0)
		{
			SetDirection(FACING_RIGHT);
			SetPosition(Vector2D(1, GetPosition().y));
		}

		if (GetPosition().y < 300 && GetPosition().y > 75 && (GetPosition().x + (m_texture->GetWidth()/2) > SCREEN_WIDTH-10))
		{
			SetDirection(FACING_LEFT);
		}
		

		//enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		//should not move when injured
		m_moving_right = false;
		m_moving_left = false;

		//count down injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightwayUp();
	}



}

bool CharacterKoopa::GetInjured()
{
	return m_injured;
}
