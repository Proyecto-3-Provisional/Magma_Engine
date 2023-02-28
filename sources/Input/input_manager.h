#pragma once

#include <string.h>
#include <iostream>

#include "input_commands.h"

class InputManager
{
public:

    InputManager(); 
    ~InputManager() {}

    void inputEvent();

    // Comandos de input de teclado
    bool keyDown(int key);
    bool keyReleased(int key);
    bool keyPressed(KeyboardKey key);

    // Comandos de input de raton
    bool mouseDown(MouseButton button);
    bool mouseReleased(MouseButton button);
    bool mousePressed(MouseButton button);

    // ¿Se debe salir del bucle ppal.?
    bool exitRequested();

private:

    bool exitRequest; 

    bool keysDown[SIZE];
    bool keysUp[SIZE];
};