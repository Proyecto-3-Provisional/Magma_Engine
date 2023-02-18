// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class Component;
class Manager;

#include <vector>

class Entity {
public:
	Entity();
	virtual ~Entity();
	inline void setContext(Manager* mngr);
	inline bool isAlive();
	inline void setAlive(bool alive);

	//insertar aqui metodos para añadir, quitar, y preguntar por componentes



	//estos dos metodos seguramente desaparezcan -> funcionalidad pasa a sistemas, estan aqui para que funcione manager por ahora
	//inline void update();
	//inline void render();

private:
	bool alive;
	Manager* mngr;
	//friend Manager;

	//cmps_ se usa para tener un acceso rápido a los componentes por identificador(posición). --> segun samir, esto desaparece en una arquitectura limpia de ecs
	//std::vector<Component*> currCmps;

	//currCmps_ se usa para recorrer a todos los componentes actuales de la entidad.
	//std::array<Component*, ecs::maxComponentId> cmps;	
};




