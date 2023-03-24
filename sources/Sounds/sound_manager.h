#pragma once

#include "SDL_audio.h"

#include <iostream>
#include <vector>

//class SDL_mixer; 

struct AudioData
{
	std::string audio_path;

	int channel;

	float volume;

	bool canLoop; 
	bool isPlaying; 
	bool isPaused; 
};

class SoundManager
{
public:

	SoundManager(); 
	~SoundManager() {}

	void addSong(std::string path, float vol, int channel, bool loop);

	void playSound(AudioData* audio);
	void stopSound(AudioData* audio);
	void pauseSound(AudioData* audio);
	void resumeSound(AudioData* audio);

	void changeVolume();
	void setVolume(float soundVolume); 
	float getVolume(); 

	void removeSong(AudioData* audio);
	bool songEnded(AudioData* audio); 

private:

	SDL_AudioDeviceID device; // Identificador del dispositivo de audio que se abre al reproducir un sonido

	float musicVolume; 

	std::vector<AudioData*> songs;
};

