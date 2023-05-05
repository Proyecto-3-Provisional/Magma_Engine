#pragma once

#include <EC/component.h>
#include <Render/text.h>

namespace magma_game
{
	class Timer : public magma_engine::Component
	{
	public:

		//Metodo de declaración del componente
		Timer();
		virtual ~Timer();

		virtual bool initComponent();

		virtual void render() {};

		//Metodos para activación o desactivación del componente
		virtual void onEnable();
		virtual void onDisable();

		//Metodo para inicializar el componente
		virtual bool start();

		//Metodo para actualizar el componente
		virtual void update(float deltaTime);

		void reset(); 
		void pause();
		void resume(); 

		int getTimer(); 

		void assignText(magma_engine::Text* text);

	private:

		magma_engine::Text* textTime;

		bool timerPause; 

		int time; 
		int timeStop; 
	};
}

