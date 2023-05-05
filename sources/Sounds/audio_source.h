#pragma once

#include <string>

#include <EC/component.h>

namespace magma_engine
{
	class SoundManager;

	struct AudioData;

	class AudioSource : public Component
	{
	public:

		AudioSource();
		virtual ~AudioSource();

		// Establece los valores iniciales del sonido
		bool initComponent(std::map<std::string, std::string> args);

		bool start();
		void update(float frameTime) override;

		// Reproduce el audio si no se est� reproduciendo
		void playSong(); 
		// Pausa la reproducci�n del audio
		void pauseSong(); 
		// Reanuda la reproducci�n del audio si se hab�a pausado previamente
		void resumeSong(); 
		// Detiene la reproducci�n del audio
		void stopSong(); 

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



