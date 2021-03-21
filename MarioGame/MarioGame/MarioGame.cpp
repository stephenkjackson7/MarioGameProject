#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//function prototypes
bool InitSDL();
bool Update();

void CloseSDL();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

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
		g_texture = LoadTextureFromFile("Images/test.bmp");
		if (g_texture == nullptr)
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
	FreeTexture();
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

	//set where to render the texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return p_texture;
}

void FreeTexture()
{
	//check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}