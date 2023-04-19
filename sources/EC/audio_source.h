#pragma once

#include <string>

#include <EC/component.h>

#include <Sounds/sound_manager.h>

class SoundManager;

struct AudioData;

namespace ec 
{
	class AudioSource : public Component
	{
	public:

		AudioSource(Entity* e, std::string path, int vol, int channel, bool loop, bool start);

		virtual ~AudioSource();

		virtual void start();
		virtual void update(int frameTime);

		void setSongsValues(std::string path, int vol, int channel, bool loop, bool start); 

		void playSong();
		void pauseSong();
		void resumeSong();
		void stopSong();

		void setVolume(int vol);
		int getVolume();

	private:

		static std::string name;

		AudioData* audio;
		SoundManager* manager; 

		bool isLoop, hasStarted, playing, paused;

		bool toPlay = false;
	};
}
