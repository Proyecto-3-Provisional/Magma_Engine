// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <vector>

#include "component.h"
#include "entity.h"
#include "ec.h"
#include "messages.h"
#include "../singleton.h"

namespace ec {
	class EntityManager : public Singleton<EntityManager> {
	public:
		EntityManager(){};
		virtual ~EntityManager();

		//Creamos una instancia de la entidad y la añadimos a la lista del grupo concreto(entsByGroup)
		// 
		// NOTA IMPORTANTE:
		//
		// Con este diseño introducimos la entidad inmediatamentes en la lista de entidades,
		// por lo que se apareceran durante este frame en la lista de entidades, si realizamos
		// alguna operacion sobre ella.
		//
		// Una solucion a esto es crear una lista auxiliar de entidades a la que
		// las añadimos, y un metodo flush() que las pase a la lista "oficial".
		// Se le llamaria al final de cada iteracion del main loop, y asi no
		// aparecen hasta el siguiente frame. Si quisieramos tambien se podria incorporar
		// en nuestro "refresh"
		template<typename T = _grp_GENERAL>
		Entity* addEntity() {

			constexpr auto gId = grpId<T>;

			auto e = new Entity();
			e->init(gId);
			e->setAlive(true);
			e->setContext(this);

			entsByGroup[gId].push_back(e);

			return e;
		}

		// Elimina las entidades muertas de las listas de grupos y las que ya no pertenecen a ningun grupo
		void refresh();

		void update(float deltaTime);
		void render();

		std::array<std::vector<Entity*>, maxGroupId> returnEntsByGroup();


		// Devuelve un vector con todas las entidades que pertenecen al grupo T
		template<typename T = _grp_GENERAL>
		inline const auto& getEntities() {
			constexpr auto gId = grpId<T>;
			return entsByGroup[gId];
		}

	private:
		//std::vector<Entity*> ents_;
		std::array<std::vector<Entity*>, maxGroupId> entsByGroup;
	};
}
