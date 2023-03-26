#pragma once

#include <iostream>
#include <vector> 
#include "../singleton.h"

class Mix_Chunk;

struct AudioData
{
	std::string audio_path = "";

	Mix_Chunk* wavSound = nullptr;

	int channel = -1;

	int volume = 0;

	bool loop = false; 
};

class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();

	void loadWAV(const char* path, int vol, int channel, bool loop);

	void playSound(int channel);
	void stopSound(int channel);
	void pauseSound(int channel);
	void resumeSound(int channel);

	bool hasEnded(int channel);

	void setVolume(int soundVolume);
	void setVolumeSongs(); 
	int getVolume();

	void initAudio();
	void closeAudio();

	void removeSong(int channel);

private:

	int volume;

	std::vector<AudioData*> songs;
};

