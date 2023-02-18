// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class Entity;

#include <vector>

class Manager {
public:
	Manager();
	virtual ~Manager();
	Entity* addEntity();

	//aqui funciones acerca de handlers y grupos, si los metemos


	//Su objetivo es borrar todas las entidades muertas, es decir las que han salido del juego en la última iteración
	void refresh();

	//seguramente haya que cambiarlos pronto
	void update();
	void render();
private:
	std::vector<Entity*> ents;
};

