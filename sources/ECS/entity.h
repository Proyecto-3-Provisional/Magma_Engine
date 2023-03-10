// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <array>
#include <vector>
#include <string>

#include "OgreEntity.h"
#include "../Render/graphical_object.h"
#include "component.h"
#include "ec.h"

namespace ec{

	class Entity {
	public:
		Entity() : mngr(), cmps(), alive(), gId(), graphObj() {};
		
		virtual ~Entity();

		bool init(ec::grpId_type gId_, GraphicalObject* graphObj_);
		//Borramos los constructores de copia y asignacion porque no queda claro como copiar componentes
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		inline GraphicalObject* getGraphObj() { 
			return graphObj; 
		};

		//Le pasamos el manager de la entidad, para que pueda referirse a el
		void setContext(EntityManager* mngr_);

		void setAlive(bool alive_);

		inline bool isAlive() {
			return alive;
		}


		//A?ade un componente a la entidad 'e'. Recibe, ademas del tipo T, los argumentos(si necesita) 
		//para pasarle a la constructora. El identificador 'cId' es cmpId<T>
		template<typename T, typename ...Ts>
		T* addComponent(Ts &&... args) {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < maxComponentId);


			removeComponent<T>();


			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(this, mngr);
			c->initComponent();
			cmps[cId] = c;
			currCmps.push_back(c);

			
			return static_cast<T*>(c);
		}

		//Elimina el componente de la entidad 'e' que este en la posicion T::id
		template<typename T>
		void removeComponent() {

			constexpr cmpId_type cId = cmpId<T>; //T::id;
			assert(cId < maxComponentId);

			if (cmps[cId] != nullptr) {

				// Encuentra el elemento igual a e->cmps_[cId]
				auto iter = std::find(currCmps.begin(), currCmps.end(),
					cmps[cId]);

				//Comprobar que tiene el componente
				assert(iter != currCmps.end());

				//Eliminarlo
				currCmps.erase(iter);

				delete cmps[cId];
				
				cmps[cId] = nullptr;
			}
		}

		//Devuelve un puntero al componente T de la entidad 'e'
		template<typename T>
		T* getComponent() {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < ec::maxComponentId);

			return static_cast<T*>(cmps[cId]);
		}

		//Devuelve true si la entidad 'e' tiene el componente T
		template<typename T>
		bool hasComponent() {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < ec::maxComponentId);

			return cmps[cId] != nullptr;
		}

		//Devuelve el grupo de la entidad 'gId'
		inline ec::grpId_type groupId() {
			return gId;
		}

		void update(float deltaTime);

		void render();

	private:

		EntityManager* mngr;
		std::vector<Component*> currCmps;
		std::array<Component*, maxComponentId> cmps;

		bool alive;
		ec::grpId_type gId;

		GraphicalObject* graphObj;

	};
}
