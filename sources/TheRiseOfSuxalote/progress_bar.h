#pragma once

#include <EC/component.h>

namespace magma_engine
{
	class UI_Progress_Bar;
}

namespace magma_game {

	class Progress_Bar : public magma_engine::Component
	{
	public:

		//Metodo de declaración del componente
		Progress_Bar();
		virtual ~Progress_Bar();

		virtual bool initComponent(std::map<std::string, std::string> args);

		virtual void render() {};

		//Metodos para activación o desactivación del componente
		virtual void onEnable();
		virtual void onDisable();

		//Metodo para obtener el nombre del componente
		std::string GetName();

		//Metodo para inicializar el componente
		virtual bool start();

		//Metodo para actualizar el componente
		//En este caso, modificamos el tamaño de la imagen si ha habido
		//cambios en el tamaño de la ventana
		virtual void update(float deltaTime);

		//Indicamos si puedes interactuar o no con el componente
		void setInteractive(bool interactive);

		//Metodos para modificar el valor del progreso actual y el limite
		void setProgress(float pro);
		void setProgressLimit(float proLimit);

	private:

		magma_engine::UI_Progress_Bar* progressBar;

		//Nombre de la imagen
		std::string imageName;
		//Nombre de la textura
		std::string normalName;

		//Booleano de interaccion o no
		bool interactive;

		//Variable del progreso actual y el final 
		float progress;
		float limit;

		int musical;

		//Variables de tamaño, posicion y tamaño de pantalla
		float tamX;
		float tamY;
		float posX;
		float posY;
	};
}

