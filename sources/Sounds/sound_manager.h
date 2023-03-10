#pragma once

#include "SDL_audio.h"

#include <iostream>

struct AudioData // Almacena y permite la reproducción de un sonido
{
	Uint8* buffer = nullptr; // Buffer que contiene los datos del sonido
	Uint32 bufferSize = 0; // Tamaño del buffer de sonido
	SDL_AudioSpec spec = {}; // Especificaciones del audio
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void playSound();
	void stopSound();
	void changeVolume();

private:
	SDL_AudioDeviceID device; // Identificador del dispositivo de audio que se abre al reproducir un sonido

	AudioData data; // Almacena los datos necesarios para reproducir un sonido
};
