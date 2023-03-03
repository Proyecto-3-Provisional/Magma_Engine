#pragma once

#include "SDL_audio.h"

#include <iostream>

typedef struct // Almacena y permite la reproducción de un sonido
{
	Uint8* buffer; // Buffer que contiene los datos del sonido
	Uint32 bufferSize; // Tamaño del buffer de sonido
	SDL_AudioSpec spec; // Especificaciones del audio
} AudioData;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void playSound();
	void stopSound();

private:
	SDL_AudioDeviceID device; // Identificador del dispositivo de audio que se abre al reproducir un sonido

	AudioData data; // Almacena los datos necesarios para reproducir un sonido
};

//class AudioBuffer {
//public:
//    AudioBuffer() {}
//
//    void updateBuffer(Uint8* stream, int len) 
//    {
//        if (audioLen == 0)
//            return;
//
//        len = (len > audioLen ? audioLen : len);
//        SDL_memcpy(stream, audioPos, len);
//        SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);
//
//        audioPos += len;
//        audioLen -= len;
//    }
//
//    void setPos(Uint8* pos) { audioPos = pos; }
//    void setLen(Uint32 len) { audioLen = len; }
//
//private:
//    Uint8* audioPos;
//    Uint32 audioLen;
//};
