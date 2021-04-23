#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H
#include <iostream>
#include "LevelMap.h"
#include "Texture2D.h"
#include "SoundEffect.h"


class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	Rect2D GetCollisionBox() { Rect2D cBox(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); return cBox; } //might not be right, check back to this if something goes wrong
	void Render();
	void TakeHit();
	bool isAvailable() { return m_num_hits_left > 0; }

protected:
	//move both back to private if this causes problem


private:
	SDL_Renderer* m_renderer;
	LevelMap* m_level_map;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
};

#endif
