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
		audio = new AudioData();

		audio->audio_path = path;

		setVolume(vol); 

		audio->channel = channel;

		isLoop = loop;
		hasStarted = start;

		playing = false;
		paused = false;

		return true; 
	}

	void AudioSource::start()
	{
		Singleton<SoundManager>::instance()->loadWAV(audio);

		if (hasStarted)
			playSong();
	}

	void AudioSource::update(float frameTime)
	{
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
		if (vol < 0)
			audio->volume = 0;
		else if (vol > 100)
			audio->volume = 100; 
		else
			audio->volume = vol;

		Singleton<SoundManager>::instance()->setVolumeSongs(); 
	}


	int AudioSource::getVolume()
	{
		return audio->volume;
	}
}



