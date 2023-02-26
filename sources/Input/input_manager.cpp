#include "input_manager.h"

void InputManager::inputEvent()
{
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode keyPressed = event.key.keysym.sym;
            std::cout << "Tecla " << char(keyPressed) << " pulsada\n";
        }

        //Liberacion de teclado
        //else if (event.type == SDL_KEYUP)
        //{
        //    std::cout << "Tecla liberada\n";
        //}

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            std::cout << "Raton apretado\n";
        }

        //Liberacion de raton
        //else if (event.type == SDL_MOUSEBUTTONUP)
        //{
        //    std::cout << "Raton liberado\n";
        //}

        else if (event.type == SDL_QUIT)
        {
            std::cout << "QUIT\n";
        }
    }
}
