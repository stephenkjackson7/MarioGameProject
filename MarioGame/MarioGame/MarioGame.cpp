<<<<<<< Updated upstream
=======
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "constants.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

//function prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			Render();
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

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr)
	{
		//init PNG loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}

		//Load the background texture
		g_texture = new Texture2D(g_renderer);

		if (!g_texture->LoadFromFile("Images/test.bmp"))
		{
			return false;
		}
	}
	else
	{
		cout << "Renderer could initialise. Error: " << SDL_GetError();
		return false;
	}

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
	//release the texture
	delete g_texture;
	g_texture = nullptr;

	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

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

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}
>>>>>>> Stashed changes
