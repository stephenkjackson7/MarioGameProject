#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"

using namespace std;

SDL_Window* g_window = nullptr;

bool InitSDL();
bool Update();
void CloseSDL();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
		g_window = SDL_CreateWindow
		("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

	if (g_window == nullptr)
	{
		cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	else
		return true;
}

void CloseSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	switch (e.type)
	{
		//click the X to quit
		case SDL_QUIT:
			return true;
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_q:
					return true;
					break;
			}
	}
	return false;
}