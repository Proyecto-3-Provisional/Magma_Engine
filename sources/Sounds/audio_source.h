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
		bool initComponent(std::map<std::string, std::string> args);

		void start();
		void update(float frameTime) override;


		void playSong(); // Reproduce el audio si no se está reproduciendo
		void pauseSong(); // Pausa la reproducción del audio
		void resumeSong(); // Reanuda la reproducción del audio si se había pausado previamente
		void stopSong(); // Detiene la reproducción del audio

		void setVolume(int vol);
		int getVolume();

	private:

		static std::string name;

		AudioData* audio;

		bool isLoop; 
		bool hasStarted; 
		bool playing; 
		bool paused;
	};
}



