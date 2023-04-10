#pragma once

#include "component.h"

#include <string>

#include "../Sounds/sound_manager.h"
class SoundManager;

struct AudioData;

namespace ec 
{
	class AudioSource : public Component
	{
	public:

		AudioSource();
		AudioSource(Entity* e, std::string path, float vol, int channel, bool loop, bool start);

		virtual ~AudioSource();

		virtual void start();
		virtual void update(int frameTime);

		void setSongsValues(std::string path, float vol, int channel, bool loop, bool start); 

		void playSong();
		void pauseSong();
		void resumeSong();
		void stopSong();

		void setVolume(float vol);
		float getVolume();

	private:

		static std::string name;

		AudioData* audio;
		SoundManager* manager; 

		bool isLoop, hasStarted, playing, paused;

		bool toPlay = false;
	};
}
