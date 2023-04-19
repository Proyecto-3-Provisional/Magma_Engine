#include <Sounds/sound_manager.h>

#include <SDL_mixer.h>
#include <SDL.h>

//Carga e inicializacion del sonido

SoundManager::SoundManager() : volume(0) {}

SoundManager::~SoundManager() 
{
	for (int i = 0; i < songs.size(); i++)
	{
		delete songs[i];
	}

	songs.clear();
}

void SoundManager::initAudio()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		std::cerr << "Error al iniciar el sistema de audio: " << SDL_GetError() << std::endl;

	//Inicializamos SDL2_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw std::exception("SDL2_mixer can't be initialized");

	volume = 1;
}

void SoundManager::closeAudio()
{
	Mix_CloseAudio();
}

void SoundManager::loadWAV(const char* path, int vol, int channel, bool loop)
{
	Mix_Chunk* wav = Mix_LoadWAV(path);

	if (wav == 0)
		std::cout << ".wav can't be loaded\n";

	AudioData* data = new AudioData; 

	data->wavSound = wav; 
	data->volume = vol; 
	data->channel = channel; 
	data->loop = loop;

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
		Mix_VolumeChunk((*it)->wavSound, volume * (*it)->volume * MIX_MAX_VOLUME);

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
	removeSong(channel);
	Mix_HaltChannel(channel);
}

bool SoundManager::hasEnded(int channel)
{
	bool end = !Mix_Playing(channel); 

	if (end)
		removeSong(channel);

	return end;
}

void SoundManager::removeSong(int channel)
{
	auto it = songs.begin(); 

	while (it != songs.end() && (*it)->channel != channel)
		it++; 

	if (it != songs.end())
		songs.erase(it); 
}

//Ajustes de volumen del sonido

void SoundManager::setVolumeSongs()
{
	for (size_t i = 0; i < songs.size(); i++) 
		Mix_VolumeChunk(songs[i]->wavSound, volume * songs[i]->volume * MIX_MAX_VOLUME);
}

void SoundManager::setVolume(int newVol) 
{
	volume = newVol;
}

int SoundManager::getVolume() 
{
	return volume;
}

