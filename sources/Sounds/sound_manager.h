#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector> 
#include <singleton.h>

class Mix_Chunk;

namespace magma_engine
{
	//Struct con informacion de las canciones 
	struct AudioData
	{
		//Ruta de la cancion
		std::string audio_path = "";

		//Sonido en wav
		Mix_Chunk* wavSound = nullptr;

		//Canal y volumen
		int channel = -1;
		int volume = 0;

		//Booleano de bucle o no 
		bool loop = false;
	};

	class MAGMAENGINE_API SoundManager : public Singleton<SoundManager>
	{
	public:
		SoundManager();
		~SoundManager();

		//Metodo para cargar los sonidos y poder ejecutarlos
		bool loadWAV(AudioData* data);

		//Metodos para activar, parar, pausar y continuar con los sonidos
		void playSound(int channel);
		void stopSound(int channel);
		void pauseSound(int channel);
		void resumeSound(int channel);

		//Booleano que comprueba si ha terminado la cancion o no
		bool hasEnded(int channel);

		//Metodos para indicar el volumen, cambiar el volumen de todas 
		//las canciones y obtener el valor actual 
		void setVolume(float soundVolume);
		void setVolumeSongs();
		float getVolume();

		//Metodo para inicializar el audio o cerrarlo
		bool initAudio();
		void closeAudio();

		//Metodo para eliminar canciones
		void removeSong(int channel);

	private:

		//Volumen general (De 0 a 1)
		float volume;

		//Vector de canciones
		std::vector<AudioData*> songs;
	};
}



