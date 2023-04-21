#include <EC/component.h>

#include <string>

class UIButton;

class Button : public ec::Component
{
public:

	//Metodo de declaraci�n del componente
	Button(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName,
		float width, float height, float x, float y);

	virtual ~Button();

	virtual bool initComponent();

	virtual void render() {};

	//Metodos para activaci�n o desactivaci�n del componente
	virtual void onEnable();
	virtual void onDisable();

	//Metodo para obtener el nombre del componente
	std::string GetName();

	//Metodo para inicializar el componente
	virtual void start();

	//Metodo para actualizar el componente
	//En este caso, modificamos el tama�o del boton si ha habido
	//cambios en el tama�o de la ventana o modificamos el boton si ha sido pulsado
	virtual void update(float deltaTime);

	//Indicamos si puedes interactuar o no con el componente
	void setInteractive(bool interactive);

	//Comprobamos si el cursor est� en los limites del bot�n y si
	//ha sido pulsado
	bool isCursorInsideBounds(int x, int y);
	bool isButtonPressed();

private:

	UIButton* button;

	//Nombre del boton
	std::string buttonName;
	//Nombres de las texturas del boton segun su estado
	std::string normalButtonName;
	std::string hoverButtonName;
	std::string pressedButtonName;

	//Booleano de boton presionado o no, y de interactuable o no
	bool pressed;
	bool interactive;

	//Variables de tama�o, posicion y tama�o de pantalla
	float tamX;
	float tamY;
	float posX;
	float posY;
	float screenHeight;
	float screenWidth;
};