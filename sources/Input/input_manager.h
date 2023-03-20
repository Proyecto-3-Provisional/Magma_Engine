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

    void flush();

    // ¿Se debe salir del bucle ppal.?
    bool exitRequested();

    // COMANDOS TECLADO

    //Scancode es la posicion fisica de las teclas
    bool isKeyDown(ScancodeKey key);
    bool isKeyReleased(ScancodeKey key);

    // COMANDOS RATÓN

    bool isMouseDown();
    bool isMouseReleased();

    bool isMousePressed(MouseButton button);

    std::pair<int, int> getMousePos(); 

    void mouseMovement(const SDL_Event& event);

    void showOrHideMouse(); 

    bool hasWindowChange(); 

private:

    bool exitRequest;

    bool cursorState;

    bool windowChange; 

    // TECLADO 

    bool isKeyDownEvent; 
    bool isKeyReleasedEvent;

    bool keysDown[SIZE];

    // RATON

    bool isMouseButtonDown;
    bool isMouseButtonUp;

    bool mouseButtonsDown[MOUSE_MAX]; 

    std::pair<int, int> mousePos; 
};