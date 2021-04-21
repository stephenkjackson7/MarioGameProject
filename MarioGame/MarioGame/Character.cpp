#include "Character.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map)
{
	m_alive = true;
	m_current_level_map = map;
	m_moving_left = false;
	m_moving_right = false;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_RIGHT;
	m_collision_radius = 15.0f;
	m_can_jump = true;
	m_jumping = false;
	m_jump_force = 0.0f;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE, 0.0f);
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int head_position = (int)(m_position.y) / TILE_HEIGHT;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;


	//if  character walks into bottom left pipe, teleports to top right
	if (GetPosition().y > 300 && GetPosition().x < 0)
	{
		SetPosition(Vector2D((SCREEN_WIDTH - m_texture->GetWidth()), 25));
	}
	//if character walks into top left pipe, teleports to bottom right
	if (GetPosition().y < 75 && (GetPosition().x < 0))
	{
		SetPosition(Vector2D((SCREEN_WIDTH - m_texture->GetWidth()), 340));
	}

	//if character walks into bottom right pipe, teleports to top left pipe
	if (GetPosition().y > 300 && (GetPosition().x + m_texture->GetWidth() > SCREEN_WIDTH))
	{
		SetPosition(Vector2D(1, 25));
	}

	//if character walks into top right pipe, teleports to bottom left pipe
	if (GetPosition().y < 75 && (GetPosition().x + m_texture->GetWidth() > SCREEN_WIDTH))
	{
		SetPosition(Vector2D(1, 340));
	}



	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}


	if (m_current_level_map->GetTileAt(head_position, centralX_position) == 1)
	{
		CancelJump();
	}

	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;

	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}
void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	if ((m_position.y + 64) <= SCREEN_HEIGHT)
		m_position.y += GRAVITY * deltaTime;

	else
		m_can_jump = true;
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::AddWindowCollision()
{
	//stops from exiting screen to left
	if (GetPosition().y < 300 && GetPosition().y > 100 && GetPosition().x < 0)
	{
		SetPosition(Vector2D(1, GetPosition().y));
	}

	//stops from exiting screen to right
	if (GetPosition().y < 300 && GetPosition().y > 100 && (GetPosition().x + (m_texture->GetWidth() / 2) > SCREEN_WIDTH - 10))
	{
		SetPosition(Vector2D(SCREEN_WIDTH - (m_texture->GetWidth() - 3), GetPosition().y));
	}
}

void Character::Bounce(float deltaTime)
{
	m_jump_force = INITIAL_JUMP_FORCE;
	m_position.y -= m_jump_force * deltaTime;
}
