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

	bool AudioSource::initComponent(std::map<std::string, std::string> args)
	{
		try {

			audio = new AudioData();

			audio->audio_path = "./assets/sounds/" + args["path"];
			audio->volume = stoi(args["vol"]);
			audio->channel = stoi(args["channel"]);

			isLoop = stoi(args["loop"]);
			hasStarted = stoi(args["start"]);

			playing = false;
			paused = false;

			if (audio->audio_path == "")
			{
				std::cout << "WARNING! - No hay un archivo de sonido en AudioSource \n\n";
				return false;
			}
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente AudioSource:\n\n     " << e.what() << "\n\n";
			return false;
		}

		return true;
	}

	bool AudioSource::start()
	{
		if (!Singleton<SoundManager>::instance()->loadWAV(audio))
		{
			std::cout << "WARNING! - error al cargar un sonido WAV, se recomienda mirar si el archivo existe o si esta bien escrito su nombre \n\n";
			return false;
		}

		if (hasStarted)
			playSong();

		return true;
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



