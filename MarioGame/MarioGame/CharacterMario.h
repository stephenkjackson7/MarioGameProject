#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTER_MARIO_H
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void WalkAnimation();
private:
	float m_single_sprite_h;
	float m_single_sprite_w;
	int m_frame_count;
	int m_last_tick;
	int m_current_frame_time;
};

#endif
