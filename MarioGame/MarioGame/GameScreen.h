#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include <SDL.h>
#include <string>
#include "Texture2D.h"
#include <iostream>

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool SetBackground(string path);

protected:
	SDL_Renderer* m_renderer;
	Texture2D* m_background_texture;

private:
	
};

#endif

