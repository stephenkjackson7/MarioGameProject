#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "PowBlock.h"

class PowBlock;
class Character;
class Texture2D;


class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();

private:
	CharacterMario* mario;
	CharacterLuigi* luigi;
	Texture2D* m_background_texture;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	void SetLevelMap();
	bool SetUpLevel();

};

#endif
