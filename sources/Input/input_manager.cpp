#include "input_manager.h"

InputManager::InputManager() 
{
	exitRequest = false; 
}

bool InputManager::exitRequested()
{
	return exitRequest; 
}

void InputManager::inputEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// Los siguientes comandos cierran el main
		// CRUZ DE CIERRE
		case SDL_QUIT: 
			exitRequest = true;
			break;
		// TECLA 'ESCAPE'
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				exitRequest = true;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		default:
			break;
		}
	}
}
