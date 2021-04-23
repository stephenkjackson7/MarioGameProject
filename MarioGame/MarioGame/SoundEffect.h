#pragma once
#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H
#include <SDL_mixer.h>
#include <iostream>

class SoundEffect
{
public:
	Mix_Chunk* g_high = NULL;
	SoundEffect();
	~SoundEffect();

	void Load(std::string path);
	void Play();
	void FreeSound();

private:

};

#endif
