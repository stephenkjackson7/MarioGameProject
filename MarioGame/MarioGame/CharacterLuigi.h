#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

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

