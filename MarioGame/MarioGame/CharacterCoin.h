#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H
#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterCoin();

	virtual void Render();
	void Update();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_current_frame_time;
	int m_frame_count;
	int lastTick;

};

#endif
