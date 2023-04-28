#include <Sounds/audio_source.h>
#include <Sounds/sound_manager.h>

namespace magma_engine
{
	AudioSource::AudioSource() : Component()
	{
		
	}

	AudioSource::~AudioSource()
	{
		stopSong();
		delete audio;
	}

	bool AudioSource::initComponent(std::string path, int vol, int channel, bool loop, bool start)
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
		Singleton<SoundManager>::instance()->loadWAV(audio->audio_path.c_str(), audio->volume, audio->channel, isLoop);

		if (hasStarted)
			playSong();
	}

	void AudioSource::update(int frameTime)
	{
		playSong();

		playing = !Singleton<SoundManager>::instance()->hasEnded(audio->channel);

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

			Singleton<SoundManager>::instance()->playSound(audio->channel);
			playing = true;
			toPlay = false;
		}
	}

	void AudioSource::pauseSong()
	{
		if (playing && !paused)
		{
			Singleton<SoundManager>::instance()->pauseSound(audio->channel);
			paused = true;
		}
	}

	void AudioSource::resumeSong()
	{
		if (playing && paused)
		{
			Singleton<SoundManager>::instance()->resumeSound(audio->channel);
			paused = false;
		}
	}

	void AudioSource::stopSong()
	{
		if (playing || paused)
		{
			Singleton<SoundManager>::instance()->stopSound(audio->channel);

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



