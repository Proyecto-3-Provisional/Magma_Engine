#pragma once

#include <EC/component.h>
#include <map>
#include <string>

namespace magma_engine
{
	class UI_Image;

	class Image : public Component
	{
	public:

		//Metodo de declaraci�n del componente
		Image();
		virtual ~Image();

		virtual bool initComponent(std::map<std::string, std::string> args);

		virtual void render() {};

		//Metodos para activaci�n o desactivaci�n del componente
		virtual void onEnable();
		virtual void onDisable();

		//Metodo para obtener el nombre del componente
		std::string GetName();

		//Metodo para inicializar el componente
		virtual bool start();

		//Metodo para actualizar el componente
		//En este caso, modificamos el tama�o de la imagen si ha habido
		//cambios en el tama�o de la ventana
		virtual void update(float deltaTime);

		//Indicamos si puedes interactuar o no con el componente
		void setInteractive(bool interactive);

		//Metodo para cambiar la textura de la imagen
		void changeImage(std::string newImage);

	private:

		static std::string name;
		UI_Image* image;

		//Nombre de la imagen
		std::string imageName;
		//Nombre de la textura
		std::string normalName;

		//Booleano de interaccion o no
		bool interactive;

		//Variables de tama�o, posicion y tama�o de pantalla
		float tamX;
		float tamY;
		float posX;
		float posY;
		float screenHeight;
		float screenWidth;
	};
}

