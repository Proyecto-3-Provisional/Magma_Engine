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

		AudioSource(std::string path, int vol, int channel, bool loop, bool start);

		virtual ~AudioSource();

		virtual void start();
		virtual void update(int frameTime);

		// Establece los valores iniciales del sonido
		void setSongsValues(std::string path, int vol, int channel, bool loop, bool start);

		void playSong(); // Reproduce el audio si no se est� reproduciendo
		void pauseSong(); // Pausa la reproducci�n del audio
		void resumeSong(); // Reanuda la reproducci�n del audio si se hab�a pausado previamente
		void stopSong(); // Detiene la reproducci�n del audio

		void setVolume(int vol);
		int getVolume();

	private:

		static std::string name;

		AudioData* audio;

		bool isLoop, hasStarted, playing, paused;

		bool toPlay = false;
	};
}



