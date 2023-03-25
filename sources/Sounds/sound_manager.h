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

	bool loop; 
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void loadWAV(const char* path, float vol, int channel, bool loop);

	void playSound(int channel);
	void stopSound(int channel);
	void pauseSound(int channel);
	void resumeSound(int channel);

	bool hasEnded(int channel);

	void setVolume(float soundVolume);
	void setVolumeSongs(); 
	float getVolume();

	void initAudio();
	void closeAudio();

	void removeSong(int channel);

private:

	float volume;

	std::vector<AudioData*> songs;
};

