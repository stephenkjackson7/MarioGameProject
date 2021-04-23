#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::Load(std::string path)
{
	//no file loads into g_high, can't debug because whole program closes before I can read the window
	g_high = Mix_LoadWAV(path.c_str());
	if (g_high == nullptr)
	{
		std::cout << "Failed to load music. Error " << Mix_GetError() << std::endl;
	}
}

void SoundEffect::Play()
{
	Mix_PlayChannel(-1, g_high, 0);
}

void SoundEffect::FreeSound()
{
	Mix_FreeChunk(g_high);
	g_high = nullptr;
}