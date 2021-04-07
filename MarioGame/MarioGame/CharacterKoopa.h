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

	bool GetInjured();

private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;


	void FlipRightwayUp();

};

#endif
