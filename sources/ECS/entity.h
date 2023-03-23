// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <array>
#include <vector>
#include <string>

#include "component.h"
#include "ec.h"

namespace ec{

	class Entity {
	public:
		Entity() : mngr(), cmps(), alive(), gId() {};
		
		virtual ~Entity();

		bool init(ec::grpId_type gId_);
		//Borramos los constructores de copia y asignacion porque no queda claro como copiar componentes
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		//Le pasamos el manager de la entidad, para que pueda referirse a el
		void setContext(EntityManager* mngr_);

		void setAlive(bool alive_);

		inline bool isAlive() {
			return alive;
		}


		// Añade un componente a la entidad 'e'. Recibe, ademas del tipo T, los argumentos(si necesita) 
		// para pasarle a la constructora. El identificador 'cId' es cmpId<T>
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

		// Elimina el componente de la entidad 'e' que este en la posicion T::id
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

		// Devuelve un puntero al componente T de la entidad 'e'
		template<typename T>
		T* getComponent() {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < ec::maxComponentId);

			return static_cast<T*>(cmps[cId]);
		}

		// Devuelve true si la entidad 'e' tiene el componente T
		template<typename T>
		bool hasComponent() {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < ec::maxComponentId);

			return cmps[cId] != nullptr;
		}

		// Devuelve el grupo de la entidad 'gId'
		inline ec::grpId_type groupId() {
			return gId;
		}

		void update(float deltaTime);

		void render();

		// Manda un mensaje 'm' a todos los componentes de la entidad. 'delay' indica si deberia
		// mandarse inmediatamente o mas tarde cuando llamamos a flushMessages
		inline void send(const Message& m, bool delay = false) {
			if (!delay) {
				for (Component* c : cmps) {
					if (c != nullptr)
						c->recieve(m);
				}
			}
			else {
				msgs_.emplace_back(m);
			}
		}

		// Metodo que se llama en main para mandar mensajes en una cola.
		// Esto es, cuando send tiene delay = true
		inline void flushMessages() {

			// we traverse until msgs_.size(), so if new message
			// we added we don't send them now. If you wish to send
			// them as will you should write this loop in a different way
			// and maybe using std::list would be better.

			auto size = msgs_.size();
			for (auto i = 0u; i < size; i++) {
				auto& m = msgs_[i];
				for (Component* c : cmps) {
					if (c != nullptr)
						c->recieve(m);
				}
			}

			// delete all message that we have sent. This might be expensive
			// since it has to shift all remaining elements to the left. A better
			// solution would be to keep two vectors 'v1' and 'v2', when sending a
			// message we always add it to 'v1' and in flush we swap them and send
			// all messages in v2. After flush we simply clear v2
			
			msgs_.erase(msgs_.begin(), msgs_.begin() + size);
		}

	private:

		EntityManager* mngr;
		std::vector<Component*> currCmps;
		std::array<Component*, maxComponentId> cmps;

		bool alive;
		ec::grpId_type gId;

		std::vector<Message> msgs_;
		std::vector<Message> msgs_aux_;
	};
}
