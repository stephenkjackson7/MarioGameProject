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
	void Update(float deltaTime, SDL_Event e);

	bool m_animate;
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	

};

#endif
