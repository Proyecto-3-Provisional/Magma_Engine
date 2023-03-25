#include "sound_manager.h"

#include <SDL_mixer.h>
#include <SDL.h>

//Carga e inicializacion del sonido

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {}

void SoundManager::initAudio()
{
	//Inicializamos SDL2_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw std::exception("SDL2_mixer can't be initialized");

	volume = 1;
}

void SoundManager::closeAudio()
{
	Mix_CloseAudio();
}

void SoundManager::loadWAV(const char* path)
{
	Mix_Chunk* wav = Mix_LoadWAV(path);

	if (!wav)
		std::cout << ".wav can't be loaded\n";
}

//Interacciones con el sonido

void SoundManager::playSound(AudioData* audio, int loop)
{
	songs.push_back(audio);

	Mix_VolumeChunk(audio->wavSound, volume * audio->volume * MIX_MAX_VOLUME);

	if (Mix_PlayChannel(audio->channel, audio->wavSound, loop) == -1)
		std::cout << ".wav can't be played\n";
}

void SoundManager::pauseSound(AudioData* audio)
{
	Mix_Pause(audio->channel);
}

void SoundManager::resumeSound(AudioData* audio)
{
	Mix_Resume(audio->channel);
}

void SoundManager::stopSound(AudioData* audio)
{
	removeSong(audio);
	Mix_HaltChannel(audio->channel);
}

bool SoundManager::hasEnded(AudioData* audio)
{
	bool end = !Mix_Playing(audio->channel); 

	if (end)
		removeSong(audio);

	return end;
}

void SoundManager::removeSong(AudioData* audio)
{
	for (auto it = songs.begin(); it != songs.end(); ++it)
	{
		if ((*it) == audio)
		{
			songs.erase(it);
			delete (*it);
			break;
		}
	}
}

//Ajustes de volumen del sonido

void SoundManager::setVolumeSongs()
{
	for (size_t i = 0; i < songs.size(); i++) 
		Mix_VolumeChunk(songs[i]->wavSound, volume * songs[i]->volume * MIX_MAX_VOLUME);
}

void SoundManager::setVolume(float newVol) 
{
	volume = newVol;
}

float SoundManager::getVolume() 
{
	return volume;
}

