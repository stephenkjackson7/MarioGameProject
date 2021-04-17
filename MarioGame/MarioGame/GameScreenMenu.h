#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H
#include "GameScreen.h"

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
};
#endif
