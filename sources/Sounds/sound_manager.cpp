#include <Sounds/sound_manager.h>

#include <SDL_mixer.h>
#include <SDL.h>

namespace magma_engine
{
	SoundManager::SoundManager() : volume(0) {}

	SoundManager::~SoundManager()
	{
		{
		songs.clear();
	}

	bool SoundManager::initAudio()
	{
		if (SDL_Init(SDL_INIT_AUDIO) != 0) {
			std::cerr << "Error al iniciar el sistema de audio: " << SDL_GetError() << std::endl;
			return false;
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			throw std::exception("SDL2_mixer can't be initialized");
			return false;
		}

		volume = 1;
		return true;
	}

	void SoundManager::closeAudio()
	{
		Mix_CloseAudio();
	}

	void SoundManager::loadWAV(AudioData* data)
	{
		Mix_Chunk* wav = Mix_LoadWAV(data->audio_path.c_str());

		if (wav == 0)
			std::cout << ".wav can't be loaded\n";

		data->wavSound = wav;

		songs.push_back(data);
	}

	//Interacciones con el sonido

	void SoundManager::playSound(int channel)
	{
		auto it = songs.begin();

		while (it != songs.end() && (*it)->channel != channel)
			it++;

		if (it != songs.end())
		{
			Mix_VolumeChunk((*it)->wavSound, volume * (*it)->volume);

			if (Mix_PlayChannel((*it)->channel, (*it)->wavSound, (*it)->loop) == -1)
				std::cout << ".wav can't be played\n";
		}

		else
			std::cout << ".wav doesn't exist\n";
	}

	void SoundManager::pauseSound(int channel)
	{
		Mix_Pause(channel);
	}

	void SoundManager::resumeSound(int channel)
	{
		Mix_Resume(channel);
	}

	void SoundManager::stopSound(int channel)
	{
		Mix_HaltChannel(channel);
	}

	bool SoundManager::hasEnded(int channel)
	{
		return !Mix_Playing(channel);
	}

	void SoundManager::removeSong(int channel)
	{
		auto it = songs.begin();

		while (it != songs.end() && (*it)->channel != channel)
			it++;

		if (it != songs.end()) {
			delete (*it);
			songs.erase(it);
		}
	}

	//Ajustes de volumen del sonido

	void SoundManager::setVolumeSongs()
	{
		for (size_t i = 0; i < songs.size(); i++)
			Mix_VolumeChunk(songs[i]->wavSound, volume * songs[i]->volume);
	}

	void SoundManager::setVolume(float newVol)
	{
		if (newVol > 1)
			volume = 1;
		else if (newVol < 0)
			volume = 0; 
		else
			volume = newVol;
	}

	float SoundManager::getVolume()
	{
		return volume;
	}
}



