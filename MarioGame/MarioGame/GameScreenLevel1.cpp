#include <iostream>
#include "GameScreenLevel1.h"
#include "Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetBackground("Images/BackgroundMB.png");
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mario;
	delete luigi;
	delete m_pow_block;
	m_enemies.clear();
	//m_coins.clear();

	m_background_texture = nullptr;
	mario = nullptr;
	luigi = nullptr;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	
	
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
	

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draw characters
	if (mario->GetAlive())
	{
		mario->Render();
	}
	if (luigi->GetAlive())
	{
		luigi->Render();
	}
	m_pow_block->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (!mario->GetAlive() && !luigi->GetAlive())
	{
		//Need to try communicating with Screen Manager to switch to game over screen.	
	}

	//do screenshake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}

	}

	//update character
	if (mario->GetAlive())
	{
		mario->Update(deltaTime, e);
	}

	if (luigi->GetAlive())
	{
		luigi->Update(deltaTime, e);
	}

	//Try figure out why this isn't working - probably Missing something obvious.

	
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
}

void GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	{
		m_screenshake = false;
		m_background_yPos = 0.0f;
	}
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(416, 330), m_level_map);
	SpawnCoins();
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								 	   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };


	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->isAvailable())
		{
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->isAvailable())
		{
			if (luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}



void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	//make each koopa take damage
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if enemy is on bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is enemy off screen to left/right?
				if	(	m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f)
						||
						m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f)
					)
					m_enemies[i]->SetAlive(false);
			}

			//now do the update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f)
				&&
				(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignores collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if ((mario->GetPosition().y + 16) < m_enemies[i]->GetPosition().y)
					{
						mario->SetPosition(Vector2D(mario->GetPosition().x, mario->GetPosition().y - 30));
						m_enemies[i]->TakeDamage();
					}

					else if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						mario->SetAlive(false);
						mario->SetPosition(Vector2D(1000, 1000));
						cout << "Mario has died.";
					}


				}
				if (Collisions::Instance()->Circle(m_enemies[i], luigi))
				{
					if ((luigi->GetPosition().y + 16) < m_enemies[i]->GetPosition().y)
					{
						m_enemies[i]->TakeDamage();
						luigi->SetPosition(Vector2D(luigi->GetPosition().x, luigi->GetPosition().y - 30));
					}

					else if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						luigi->SetAlive(false);
						luigi->SetPosition(Vector2D(1000, 1000));
						cout << "Luigi has died.";
					}
				}
			}

			//if enemy is no longer alive then schedule for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			//now do the update
			m_coins[i]->Update();
			

			if (Collisions::Instance()->Circle(m_coins[i], mario) || Collisions::Instance()->Circle(m_coins[i], luigi))
			{
				m_coins[i]->SetAlive(false);

			}

			//if enemy is no longer alive then schedule for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}


void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
	m_coins.push_back(coin);
}

void GameScreenLevel1::SpawnCoins()
{
	//bot-left
	CreateCoin(Vector2D(100, 260));
	CreateCoin(Vector2D(136, 260));
	CreateCoin(Vector2D(172, 260));
	//bot-right
	CreateCoin(Vector2D(316, 260));
	CreateCoin(Vector2D(352, 260));
	CreateCoin(Vector2D(388, 260));
}
