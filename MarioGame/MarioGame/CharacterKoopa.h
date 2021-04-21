#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetDirection(FACING direction);
	bool GetInjured();

private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	int m_frame_count;
	int m_last_tick;
	int m_current_frame_time;


	void FlipRightwayUp();

};

#endif
