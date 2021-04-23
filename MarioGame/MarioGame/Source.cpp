#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "GameScreenLevel1.h"

GameScreenManager* game_screen_manager;
Uint32 g_old_time;

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Mix_Music* g_music = nullptr;

//function prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();
void LoadMusic(string path);

bool CanStart = 0;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		CanStart = 1;
		
		//set the time
		g_old_time = SDL_GetTicks();
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not init. Error: " << Mix_GetError();
		return false;
	}

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
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;

	//destroy game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();


}



bool Update()
{
	Uint32 new_time = SDL_GetTicks();

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

				case SDLK_RETURN:
					if (CanStart)
					{
						LoadMusic("Music/Mario.mp3");

						if (Mix_PlayingMusic() == 0)
						{
							Mix_PlayMusic(g_music, -1);
						}
						delete game_screen_manager;
						game_screen_manager = nullptr;
						game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
						CanStart = 0;
					}
					break;
			}


	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);
}

void LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error " << Mix_GetError() << endl;
	}
}