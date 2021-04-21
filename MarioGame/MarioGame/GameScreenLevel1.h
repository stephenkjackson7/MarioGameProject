#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <vector>
#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
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
	CharacterKoopa* koopa;
	CharacterCoin* coin;
	vector<CharacterCoin*> m_coins;
	vector<CharacterKoopa*> m_enemies;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();
	void SetLevelMap();
	void SetUpLevel();
	void UpdateCoins(float deltaTime, SDL_Event e);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
	void SpawnCoins();

};

#endif
