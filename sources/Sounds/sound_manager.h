#pragma once

#include <iostream>
#include <vector> 

class Mix_Chunk;

struct AudioData
{
	std::string audio_path;

	Mix_Chunk* wavSound;

	int channel;

	float volume;
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void loadWAV(const char* path);

	void playSound(AudioData* audio, int loop = 0);
	void stopSound(AudioData* audio);
	void pauseSound(AudioData* audio);
	void resumeSound(AudioData* audio);

	bool hasEnded(AudioData* audio);

	void setVolume(float soundVolume);
	void setVolumeSongs(); 
	float getVolume();

	void initAudio();
	void closeAudio();

	void removeSong(AudioData* audio);

private:

	float volume;

	std::vector<AudioData*> songs;
};

