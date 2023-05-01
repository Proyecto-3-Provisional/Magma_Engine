#pragma once

#include <EC/component.h>
#include <map>
#include <string>

namespace magma_engine
{
	class UI_Text;

	class Text : public ec::Component
	{
	public:

		//Metodo de declaración del componente
		Text();
		virtual ~Text();

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
		//En este caso, modificamos el tamaño del texto si ha habido
		//cambios en el tamaño de la ventana
		virtual void update(float deltaTime);

		//Metodos para cambiar el contenido, la fuente, el
		//tamaño o el color del texto
		void changeText(std::string newText);
		void changeFontText(std::string newFont);
		void changeSizeText(float size);
		void changeColorText(float r, float g, float b);

	private:

		UI_Text* text;

		//Referencia al texto
		std::string textReference;
		//Nombre del texto 
		std::string textTitle;
		//Nombre de la fuente del texto
		std::string fontName;
		//Contenido del texto
		std::string textContent;

		//Variables de tamaño, color, posicion y tamaño de pantalla
		float posX;
		float posY;
		float tamX;
		float tamY;
		float red;
		float green;
		float blue;
		float screenHeight;
		float screenWidth;
	};
}

