#pragma once

#include <singleton.h>
#include <Input/input_commands.h>

namespace magma_engine
{
    class InputManager : public Singleton<InputManager>
    {
    public:

        InputManager();
        ~InputManager() {}

        void inputEvent();

        //Resetea los valores de los booleanos  
        void flush();

        //Comprueba si se debe salir del bucle principal
        bool exitRequested();
        void exitPetition(); 

        // COMANDOS TECLADO

        //Metodos que comprueban si una tecla ha sido pulsada o liberada
        //(Las teclas son Scancode, que es su posicion fisica)
        bool isKeyDown(ScancodeKey key);
        bool isKeyReleased(ScancodeKey key);

        // COMANDOS RATÓN

        //Metodos que comprueban si el raton ha sido pulsado o liberado
        bool isMouseDown();
        bool isMouseReleased();

        //Devuelve las coordenadas de posicion del raton
        std::pair<int, int> getMousePos();

        //Desplaza el raton a su nueva posicion 
        void mouseMovement(const int& x, const int& y);

        //Activa o desactiva el cursor del raton 
        void showOrHideMouse();

        //Comprueba si ha cambiado el tamaño de la pantalla
        bool hasWindowChange();

    private:

        //Booleano para salir del juego 
        bool exitRequest;

        //Booleano de aparicion o no del cursor
        bool cursorState;

        //Booleano de cambio de tamaño de pantalla
        bool windowChange;

        // TECLADO 

        //Booleano de evento del teclado
        bool isKeyDownEvent;
        bool isKeyReleasedEvent;

        //Array de booleanos para el estado de cada tecla
        bool keysDown[SIZE];

        // RATON

        //Booleano de eventos del raton
        bool isMouseButtonDown;
        bool isMouseButtonUp;

        //Array de booleanos para el estado de cada boton del raton
        bool mouseButtonsDown[MOUSE_MAX];

        //Posicion del raton 
        std::pair<int, int> mousePos;
    };
}

