#pragma once

#include <string>

#include <EC/component.h>

namespace magma_engine
{
	class SoundManager;

	struct AudioData;

	class AudioSource : public ec::Component
	{
	public:

		AudioSource();
		virtual ~AudioSource();

		// Establece los valores iniciales del sonido
		virtual bool initComponent(std::string path, int vol, int channel, bool loop, bool start);

		virtual void start();
		virtual void update(int frameTime);


		void playSong(); // Reproduce el audio si no se está reproduciendo
		void pauseSong(); // Pausa la reproducción del audio
		void resumeSong(); // Reanuda la reproducción del audio si se había pausado previamente
		void stopSong(); // Detiene la reproducción del audio

		void setVolume(int vol);
		int getVolume();

	private:

		static std::string name;

		AudioData* audio;

		bool isLoop, hasStarted, playing, paused;

		bool toPlay = false;
	};
}



