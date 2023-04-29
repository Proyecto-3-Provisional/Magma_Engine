#pragma once

#include <EC/component.h>

namespace magma_engine
{
	class Text; 

	class Timer : public ec::Component
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
		virtual void start();

		//Metodo para actualizar el componente
		virtual void update(float deltaTime);

		void reset(); 
		void pause();
		void resume(); 

		int getTimer(); 

		void assignText(Text* text); 

	private:

		Text* textTime; 

		bool timerPause; 

		int time; 
		int timeStop; 
	};
}

