#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "constants.h"
#include "LevelMap.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

	bool IsJumping() { return m_jumping; };
	void CancelJump() { m_jump_force = 0.0f; };

	void SetAlive(bool isAlive) { m_alive = isAlive; };
	bool GetAlive() { return m_alive; };

	inline Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}

	void AddWindowCollision();
	void Bounce(float deltaTime);

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	bool m_alive;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_single_sprite;
	float m_jump_force;
	float m_collision_radius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

private:
	LevelMap* m_current_level_map;
};

#endif