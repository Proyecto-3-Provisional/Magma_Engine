#include "audio_source.h"
//#include "sound_manager.h"
//
//namespace ec {
//
//	AudioSource::AudioSource() : Component() {}
//
//	AudioSource::AudioSource(Entity* e, std::string path, float vol, int channel, bool loop, bool start)
//	{
//		audio = new AudioData;
//
//		audio->audio_path = path;
//		audio->volume = vol;
//		audio->channel = channel;
//
//		isLoop = loop;
//		hasStarted = start;
//
//		playing = false; 
//		paused = false;
//	}
//
//	AudioSource::~AudioSource() 
//	{
//		stopSong();
//		delete audio;
//	}
//
//	void AudioSource::setSongsValues(std::string path, float vol, int channel, bool loop, bool start)
//	{
//		audio = new AudioData;
//
//		audio->audio_path = path;
//		audio->volume = vol;
//		audio->channel = channel;
//
//		isLoop = loop;
//		hasStarted = start;
//
//		playing = false;
//		paused = false;
//	}
//
//	void AudioSource::start()
//	{
//		//manager->loadWAV(audio->audio_path.c_str()); 
//
//		if (hasStarted)
//			playSong();
//	}
//
//	void AudioSource::update(int frameTime)
//	{
//		playSong();
//
//		//playing = !manager->hasEnded(audio);
//
//		if (playing)
//			paused = false;
//	}
//
//	void AudioSource::playSong() 
//	{
//		if (!playing) 
//		{
//			int loop = 1; 
//
//			if (isLoop == -1)
//				loop = 0;
//
//			//manager->playSound(audio, loop);
//			playing = true; 
//			toPlay = false;
//		}
//	}
//
//	void AudioSource::pauseSong() 
//	{
//		if (playing && !paused) 
//		{
//			//manager->pauseSound(audio);
//			paused = true;
//		}
//	}
//
//	void AudioSource::resumeSong() 
//	{
//		if (playing && paused) 
//		{
//			//manager->resumeSound(audio);
//			paused = false;
//		}
//	}
//
//	void AudioSource::stopSong()
//	{
//		if (playing || paused) 
//		{
//			//manager->stopSound(audio);
//
//			playing = false; 
//			paused = false;
//		}
//	}
//
//
//	void AudioSource::setVolume(float vol) 
//	{
//		audio->volume = vol;
//	}
//
//
//	float AudioSource::getVolume()
//	{
//		return audio->volume;
//	}
//}
