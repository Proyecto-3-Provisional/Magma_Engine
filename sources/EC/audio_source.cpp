#include <EC/audio_source.h>

namespace ec {

	AudioSource::AudioSource(Entity* e, std::string path, int vol, int channel, bool loop, bool start) : Component()
	{
		audio = new AudioData;

		audio->audio_path = path;
		audio->volume = vol;
		audio->channel = channel;

		isLoop = loop;
		hasStarted = start;

		playing = false; 
		paused = false;
	}

	AudioSource::~AudioSource() 
	{
		stopSong();
		delete audio;
	}

	void AudioSource::setSongsValues(std::string path, int vol, int channel, bool loop, bool start)
	{
		audio = new AudioData;

		audio->audio_path = path;
		audio->volume = vol;
		audio->channel = channel;

		isLoop = loop;
		hasStarted = start;

		playing = false;
		paused = false;
	}

	void AudioSource::start()
	{
		manager->loadWAV(audio->audio_path.c_str(), audio->volume, audio->channel, isLoop); 

		if (hasStarted)
			playSong();
	}

	void AudioSource::update(int frameTime)
	{
		playSong();

		playing = !manager->hasEnded(audio->channel);

		if (playing)
			paused = false;
	}

	void AudioSource::playSong() 
	{
		if (!playing) 
		{
			int loop = 1; 

			if (!isLoop)
				loop = 0;

			manager->playSound(audio->channel);
			playing = true; 
			toPlay = false;
		}
	}

	void AudioSource::pauseSong() 
	{
		if (playing && !paused) 
		{
			manager->pauseSound(audio->channel);
			paused = true;
		}
	}

	void AudioSource::resumeSong() 
	{
		if (playing && paused) 
		{
			manager->resumeSound(audio->channel);
			paused = false;
		}
	}

	void AudioSource::stopSong()
	{
		if (playing || paused) 
		{
			manager->stopSound(audio->channel);

			playing = false; 
			paused = false;
		}
	}


	void AudioSource::setVolume(int vol) 
	{
		audio->volume = vol;
	}


	int AudioSource::getVolume()
	{
		return audio->volume;
	}
}
