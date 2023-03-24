#include "sound_manager.h"
#include "SDL_mixer.h"

#include <SDL.h>

//static Uint8* audioPos; // Puntero a la posicion del bufer de audio que se reproduce actualmente
//static Uint32 audioLen; // Longitud restante del bufer de audio por reproducir.
//
//// Copia los datos del bufer de audio al bufer de audio del dispositivo.
//void audio_callback(void* userdata, Uint8* stream, int len);
//

SoundManager::SoundManager() : device(0)
{
	SDL_Init(SDL_INIT_AUDIO);

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		std::cerr << "Error al iniciar el sistema de audio: " << SDL_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error:" << Mix_GetError() << std::endl;

	/*if (SDL_LoadWAV("../../executables/assets/loop.wav", &data.spec, &data.buffer, &data.bufferSize) == nullptr)
		std::cerr << "Error al cargar el sonido: " << SDL_GetError() << std::endl;

	data.spec.callback = audio_callback;
	data.spec.userdata = &data;

	audioPos = data.buffer;
	audioLen = data.bufferSize;*/
}

//
//SoundManager::~SoundManager() 
//{
//	SDL_FreeWAV(data.buffer);
//	SDL_CloseAudio(); // Cerrar audio al final
//}
//
//// Reproduccion de audio
//void SoundManager::playSound()
//{
//	if(SDL_OpenAudio(&data.spec, nullptr) != 0)
//		std::cerr << "Error de dispositivo de audio: " << SDL_GetError() << std::endl;
//
//	/*device = SDL_OpenAudio(&data.spec, nullptr);
//	if (device == 0) std::cerr << "Error de dispositivo de audio: " << SDL_GetError() << std::endl;*/
//
//	SDL_PauseAudio(0);
//}
//
//// Detiene la reproduccion de audio
//void SoundManager::stopSound() 
//{
//	SDL_PauseAudio(1);
//}

//void audio_callback(void* userdata, Uint8* stream, int len)
//{
//	AudioData* data = static_cast<AudioData*>(userdata);
//
//	// Comprueba si queda audio por reproducir en el bufer
//	if (audioLen == 0) 
//	{
//		audioPos = data->buffer; // Reinicia la posicion actual del bufer de audio
//		audioLen = data->bufferSize; // Reinicia la longitud restante del audio por reproducir
//	}
//
//	len = ((unsigned int)len > audioLen ? audioLen : len); // Cantidad de datos que se van a copiar (valor mínimo entre len y audioLen)
//	SDL_memcpy(stream, audioPos, len); // Copia los datos del bufer audioPos al bufer stream
//	SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME); // Mezclan de los datos copiados con los datos almacenados en stream
//
//	audioPos += len; // Actualiza la posicion del bufer para apuntar al siguiente bloque de datos
//	audioLen -= len; // Actualiza la longitud restante del bufer
//}

void SoundManager::addSong(std::string path, float vol, int channel, bool loop)
{
	AudioData* audio = new AudioData;

	Mix_Chunk* soundtrack = Mix_LoadWAV(path.c_str());

	audio->audio_path = path;
	audio->channel = channel;
	audio->volume = vol;

	audio->canLoop = loop;
	audio->isPlaying = false; 
	audio->isPaused = false;

	songs.push_back(audio);

	Mix_VolumeChunk(soundtrack, 1000);
	Mix_PlayChannel(audio->channel, soundtrack, 1);

	//playSound(audio); 
}

void SoundManager::playSound(AudioData* audio)
{
	if (!audio->isPlaying)
	{
		//Mix_VolumeChunk(soundtrack, audio->volume);
		audio->isPlaying = true; 

		std::cout << "Musica\n"; 
	}
}

void SoundManager::pauseSound(AudioData* audio)
{
	if (audio->isPlaying && !audio->isPaused)
	{
		//Mix_Pause(audio->channel);

		audio->isPaused = true; 
		audio->isPlaying = false; 
	}
}

void SoundManager::resumeSound(AudioData* audio)
{
	if (audio->isPaused)
	{
		//Mix_Resume(audio->channel);

		audio->isPaused = false; 
		audio->isPlaying = true; 
	}
}

void SoundManager::stopSound(AudioData* audio)
{
	removeSong(audio);
	//Mix_HaltChannel(audio->channel);
}

bool SoundManager::songEnded(AudioData* audio)
{
	return true; // !Mix_Playing(audio->channel);
}

void SoundManager::removeSong(AudioData* audio) 
{
	auto it = songs.begin(); 

	while (it != songs.end() && (*it) != audio)
		it++; 

	if ((*it) == audio)
	{
		songs.erase(it);
		delete (*it);
	}
}

void SoundManager::changeVolume()
{
	for (auto i = 0; i < songs.size(); i++) 
	{
		//Mix_VolumeMusic(musicVolume * songs[i]->volume * MIX_MAX_VOLUME);
	}
}

void SoundManager::setVolume(float soundVolume)
{
	musicVolume = soundVolume; 
	changeVolume(); 
}

float SoundManager::getVolume()
{
	return musicVolume; 
}